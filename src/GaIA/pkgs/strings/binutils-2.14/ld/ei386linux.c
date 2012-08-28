/* This file is is generated by a shell script.  DO NOT EDIT! */

/* Linux a.out emulation code for i386linux
   Copyright 1991, 1993, 1994, 1995, 1996, 1998, 1999, 2000, 2002, 2003
   Free Software Foundation, Inc.
   Written by Steve Chamberlain <sac@cygnus.com>
   Linux support by Eric Youngdale <ericy@cais.cais.com>

This file is part of GLD, the Gnu Linker.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#define TARGET_IS_i386linux

#include "bfd.h"
#include "sysdep.h"
#include "bfdlink.h"

#include "ld.h"
#include "ldmain.h"
#include "ldmisc.h"
#include "ldexp.h"
#include "ldlang.h"
#include "ldfile.h"
#include "ldemul.h"

static void gldi386linux_before_parse PARAMS ((void));
static bfd_boolean gldi386linux_open_dynamic_archive
  PARAMS ((const char *, search_dirs_type *, lang_input_statement_type *));
static void gldi386linux_find_address_statement
  PARAMS ((lang_statement_union_type *));
static void gldi386linux_create_output_section_statements
  PARAMS ((void));
static void gldi386linux_before_allocation PARAMS ((void));
static char *gldi386linux_get_script PARAMS ((int *isfile));

static void
gldi386linux_before_parse()
{
  const bfd_arch_info_type *arch = bfd_scan_arch ("i386");
  if (arch)
    {
      ldfile_output_architecture = arch->arch;
      ldfile_output_machine = arch->mach;
      ldfile_output_machine_name = arch->printable_name;
    }
  else
    ldfile_output_architecture = bfd_arch_i386;
  config.dynamic_link = TRUE;
  config.has_shared = TRUE;
}

/* Try to open a dynamic archive.  This is where we know that Linux
   dynamic libraries have an extension of .sa.  */

static bfd_boolean
gldi386linux_open_dynamic_archive (arch, search, entry)
     const char *arch;
     search_dirs_type *search;
     lang_input_statement_type *entry;
{
  char *string;

  if (! entry->is_archive)
    return FALSE;

  string = (char *) xmalloc (strlen (search->name)
			     + strlen (entry->filename)
			     + strlen (arch)
			     + sizeof "/lib.sa");

  sprintf (string, "%s/lib%s%s.sa", search->name, entry->filename, arch);

  if (! ldfile_try_open_bfd (string, entry))
    {
      free (string);
      return FALSE;
    }

  entry->filename = string;

  return TRUE;
}

/* This is called by the create_output_section_statements routine via
   lang_for_each_statement.  It locates any address assignment to
   .text, and modifies it to include the size of the headers.  This
   causes -Ttext to mean the starting address of the header, rather
   than the starting address of .text, which is compatible with other
   Linux tools.  */

static void
gldi386linux_find_address_statement (s)
     lang_statement_union_type *s;
{
  if (s->header.type == lang_address_statement_enum
      && strcmp (s->address_statement.section_name, ".text") == 0)
    {
      ASSERT (s->address_statement.address->type.node_class == etree_value);
      s->address_statement.address->value.value += 0x20;
    }
}

/* This is called before opening the input BFD's.  */

static void
gldi386linux_create_output_section_statements ()
{
  lang_for_each_statement (gldi386linux_find_address_statement);
}

/* This is called after the sections have been attached to output
   sections, but before any sizes or addresses have been set.  */

static void
gldi386linux_before_allocation ()
{
  if (link_info.relocateable)
    return;

  /* Let the backend work out the sizes of any sections required by
     dynamic linking.  */
  if (! bfd_i386linux_size_dynamic_sections (output_bfd, &link_info))
    einfo ("%P%F: failed to set dynamic section sizes: %E\n");
}

static char *
gldi386linux_get_script(isfile)
     int *isfile;
{
  *isfile = 1;

  if (link_info.relocateable && config.build_constructors)
    return "ldscripts/i386linux.xu";
  else if (link_info.relocateable)
    return "ldscripts/i386linux.xr";
  else if (!config.text_read_only)
    return "ldscripts/i386linux.xbn";
  else if (!config.magic_demand_paged)
    return "ldscripts/i386linux.xn";
  else
    return "ldscripts/i386linux.x";
}

struct ld_emulation_xfer_struct ld_i386linux_emulation =
{
  gldi386linux_before_parse,
  syslib_default,
  hll_default,
  after_parse_default,
  after_open_default,
  after_allocation_default,
  set_output_arch_default,
  ldemul_default_target,
  gldi386linux_before_allocation,
  gldi386linux_get_script,
  "i386linux",
  "a.out-i386-linux",
  NULL,	/* finish */
  gldi386linux_create_output_section_statements,
  gldi386linux_open_dynamic_archive,
  NULL,	/* place orphan */
  NULL,	/* set symbols */
  NULL,	/* parse args */
  NULL,	/* add_options */
  NULL,	/* handle_option */
  NULL,	/* unrecognized file */
  NULL,	/* list options */
  NULL,	/* recognized file */
  NULL,	/* find_potential_libraries */
  NULL	/* new_vers_pattern */
};
