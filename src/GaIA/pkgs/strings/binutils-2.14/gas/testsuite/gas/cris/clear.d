#objdump: -dr
#name: @OC@

# Clear instruction.

.*:     file format .*-cris

Disassembly of section \.text:
0+ <notstart>:
[ 	]+0:	0000[ ]+	bcc ( 0x2|\.\+2)
	\.\.\.

0+4 <start>:
[	 ]+4:[	 ]+7306[ 	]+clear\.b r3
[	 ]+6:[	 ]+7546[ 	]+clear\.w r5
[	 ]+8:[	 ]+7a86[ 	]+clear\.d r10
[	 ]+a:[	 ]+700a[ 	]+clear\.b \[r0\]
[	 ]+c:[	 ]+754a[ 	]+clear\.w \[r5\]
[	 ]+e:[	 ]+7a8a[ 	]+clear\.d \[r10\]
[	 ]+10:[	 ]+700e[ 	]+clear\.b \[r0\+\]
[	 ]+12:[	 ]+754e[ 	]+clear\.w \[r5\+\]
[	 ]+14:[	 ]+7a8e[ 	]+clear\.d \[r10\+\]
[	 ]+16:[	 ]+4205 700a[ 	]+clear\.b \[r2\+r0\.b\]
[	 ]+1a:[	 ]+4255 704a[ 	]+clear\.w \[r2\+r5\.b\]
[	 ]+1e:[	 ]+42a5 708a[ 	]+clear\.d \[r2\+r10\.b\]
[	 ]+22:[	 ]+4029 700a[ 	]+clear\.b \[r2\+\[r0\]\.b\]
[	 ]+26:[	 ]+4529 704a[ 	]+clear\.w \[r2\+\[r5\]\.b\]
[	 ]+2a:[	 ]+4a29 708a[ 	]+clear\.d \[r2\+\[r10\]\.b\]
[	 ]+2e:[	 ]+402d 700a[ 	]+clear\.b \[r2\+\[r0\+\]\.b\]
[	 ]+32:[	 ]+452d 704a[ 	]+clear\.w \[r2\+\[r5\+\]\.b\]
[	 ]+36:[	 ]+4a2d 708a[ 	]+clear\.d \[r2\+\[r10\+\]\.b\]
[	 ]+3a:[	 ]+5205 700a[ 	]+clear\.b \[r2\+r0\.w\]
[	 ]+3e:[	 ]+5255 704a[ 	]+clear\.w \[r2\+r5\.w\]
[	 ]+42:[	 ]+52a5 708a[ 	]+clear\.d \[r2\+r10\.w\]
[	 ]+46:[	 ]+5029 700a[ 	]+clear\.b \[r2\+\[r0\]\.w\]
[	 ]+4a:[	 ]+5529 704a[ 	]+clear\.w \[r2\+\[r5\]\.w\]
[	 ]+4e:[	 ]+5a29 708a[ 	]+clear\.d \[r2\+\[r10\]\.w\]
[	 ]+52:[	 ]+502d 700a[ 	]+clear\.b \[r2\+\[r0\+\]\.w\]
[	 ]+56:[	 ]+552d 704a[ 	]+clear\.w \[r2\+\[r5\+\]\.w\]
[	 ]+5a:[	 ]+5a2d 708a[ 	]+clear\.d \[r2\+\[r10\+\]\.w\]
[	 ]+5e:[	 ]+6205 700a[ 	]+clear\.b \[r2\+r0\.d\]
[	 ]+62:[	 ]+6255 704a[ 	]+clear\.w \[r2\+r5\.d\]
[	 ]+66:[	 ]+62a5 708a[ 	]+clear\.d \[r2\+r10\.d\]
[	 ]+6a:[	 ]+6029 700a[ 	]+clear\.b \[r2\+\[r0\]\.d\]
[	 ]+6e:[	 ]+6529 704a[ 	]+clear\.w \[r2\+\[r5\]\.d\]
[	 ]+72:[	 ]+6a29 708a[ 	]+clear\.d \[r2\+\[r10\]\.d\]
[	 ]+76:[	 ]+602d 700a[ 	]+clear\.b \[r2\+\[r0\+\]\.d\]
[	 ]+7a:[	 ]+652d 704a[ 	]+clear\.w \[r2\+\[r5\+\]\.d\]
[	 ]+7e:[	 ]+6a2d 708a[ 	]+clear\.d \[r2\+\[r10\+\]\.d\]
[	 ]+82:[	 ]+0021 700a[ 	]+clear\.b \[r2\+0\]
[	 ]+86:[	 ]+0121 700a[ 	]+clear\.b \[r2\+1\]
[	 ]+8a:[	 ]+7f21 700a[ 	]+clear\.b \[r2\+127\]
[	 ]+8e:[	 ]+5f2d 8000 700a[ 	]+clear\.b \[r2\+128\]
[	 ]+94:[	 ]+ff21 700a[ 	]+clear\.b \[r2-1\]
[	 ]+98:[	 ]+8121 700a[ 	]+clear\.b \[r2-127\]
[	 ]+9c:[	 ]+8021 700a[ 	]+clear\.b \[r2-128\]
[	 ]+a0:[	 ]+5f2d ff00 700a[ 	]+clear\.b \[r2\+255\]
[	 ]+a6:[	 ]+2a21 700a[ 	]+clear\.b \[r2\+42\]
[	 ]+aa:[	 ]+d621 700a[ 	]+clear\.b \[r2-42\]
[	 ]+ae:[	 ]+d621 700a[ 	]+clear\.b \[r2-42\]
[	 ]+b2:[	 ]+2a21 700a[ 	]+clear\.b \[r2\+42\]
[	 ]+b6:[	 ]+d621 700a[ 	]+clear\.b \[r2-42\]
[	 ]+ba:[	 ]+d621 700a[ 	]+clear\.b \[r2-42\]
[	 ]+be:[	 ]+2a21 700a[ 	]+clear\.b \[r2\+42\]
[	 ]+c2:[	 ]+d621 700a[ 	]+clear\.b \[r2-42\]
[	 ]+c6:[	 ]+2a21 700a[ 	]+clear\.b \[r2\+42\]
[	 ]+ca:[	 ]+6f2d 0000 0000 700a[ 	]+clear\.b \[r2\+0( <notstart>)?\]
[ 	]+cc:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+d2:[	 ]+0021 704a[ 	]+clear\.w \[r2\+0\]
[	 ]+d6:[	 ]+0121 704a[ 	]+clear\.w \[r2\+1\]
[	 ]+da:[	 ]+7f21 704a[ 	]+clear\.w \[r2\+127\]
[	 ]+de:[	 ]+5f2d 8000 704a[ 	]+clear\.w \[r2\+128\]
[	 ]+e4:[	 ]+ff21 704a[ 	]+clear\.w \[r2-1\]
[	 ]+e8:[	 ]+ff21 704a[ 	]+clear\.w \[r2-1\]
[	 ]+ec:[	 ]+8121 704a[ 	]+clear\.w \[r2-127\]
[	 ]+f0:[	 ]+8021 704a[ 	]+clear\.w \[r2-128\]
[	 ]+f4:[	 ]+5f2d 7fff 704a[ 	]+clear\.w \[r2-129\]
[	 ]+fa:[	 ]+8121 704a[ 	]+clear\.w \[r2-127\]
[	 ]+fe:[	 ]+8021 704a[ 	]+clear\.w \[r2-128\]
[	 ]+102:[	 ]+5f2d 7fff 704a[ 	]+clear\.w \[r2-129\]
[	 ]+108:[	 ]+5f2d ff00 704a[ 	]+clear\.w \[r2\+255\]
[	 ]+10e:[	 ]+5f2d 01ff 704a[ 	]+clear\.w \[r2-255\]
[	 ]+114:[	 ]+5f2d 01ff 704a[ 	]+clear\.w \[r2-255\]
[	 ]+11a:[	 ]+5f2d 0001 704a[ 	]+clear\.w \[r2\+256\]
[	 ]+120:[	 ]+5f2d 00ff 704a[ 	]+clear\.w \[r2-256\]
[	 ]+126:[	 ]+5f2d 68dd 704a[ 	]+clear\.w \[r2-8856\]
[	 ]+12c:[	 ]+5f2d 68dd 704a[ 	]+clear\.w \[r2-8856\]
[	 ]+132:[	 ]+5f2d 9822 704a[ 	]+clear\.w \[r2\+8856\]
[	 ]+138:[	 ]+2a21 704a[ 	]+clear\.w \[r2\+42\]
[	 ]+13c:[	 ]+d621 704a[ 	]+clear\.w \[r2-42\]
[	 ]+140:[	 ]+d621 704a[ 	]+clear\.w \[r2-42\]
[	 ]+144:[	 ]+2a21 704a[ 	]+clear\.w \[r2\+42\]
[	 ]+148:[	 ]+d621 704a[ 	]+clear\.w \[r2-42\]
[	 ]+14c:[	 ]+d621 704a[ 	]+clear\.w \[r2-42\]
[	 ]+150:[	 ]+d621 704a[ 	]+clear\.w \[r2-42\]
[	 ]+154:[	 ]+2a21 704a[ 	]+clear\.w \[r2\+42\]
[	 ]+158:[	 ]+5f2d ff7f 704a[ 	]+clear\.w \[r2\+32767\]
[	 ]+15e:[	 ]+6f2d 0080 0000 704a[ 	]+clear\.w \[r2\+(32768|8000 <three2767\+0x1>)\]
[	 ]+166:[	 ]+6f2d 0180 0000 704a[ 	]+clear\.w \[r2\+(32769|8001 <three2767\+0x2>)\]
[	 ]+16e:[	 ]+5f2d 0180 704a[ 	]+clear\.w \[r2-32767\]
[	 ]+174:[	 ]+5f2d 0080 704a[ 	]+clear\.w \[r2-32768\]
[	 ]+17a:[	 ]+6f2d ff7f ffff 704a[ 	]+clear\.w \[r2\+[^]]+\]
[	 ]+182:[	 ]+5f2d 0180 704a[ 	]+clear\.w \[r2-32767\]
[	 ]+188:[	 ]+5f2d 0080 704a[ 	]+clear\.w \[r2-32768\]
[	 ]+18e:[	 ]+6f2d ff7f ffff 704a[ 	]+clear\.w \[r2\+[^]]+\]
[	 ]+196:[	 ]+6f2d ffff 0000 704a[ 	]+clear\.w \[r2\+(65535|ffff <six5535>)\]
[	 ]+19e:[	 ]+6f2d 0000 0000 704a[ 	]+clear\.w \[r2\+0( <notstart>)?\]
[ 	]+1a0:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+1a6:[	 ]+0021 708a[ 	]+clear\.d \[r2\+0\]
[	 ]+1aa:[	 ]+0121 708a[ 	]+clear\.d \[r2\+1\]
[	 ]+1ae:[	 ]+7f21 708a[ 	]+clear\.d \[r2\+127\]
[	 ]+1b2:[	 ]+5f2d 8000 708a[ 	]+clear\.d \[r2\+128\]
[	 ]+1b8:[	 ]+ff21 708a[ 	]+clear\.d \[r2-1\]
[	 ]+1bc:[	 ]+ff21 708a[ 	]+clear\.d \[r2-1\]
[	 ]+1c0:[	 ]+8121 708a[ 	]+clear\.d \[r2-127\]
[	 ]+1c4:[	 ]+8021 708a[ 	]+clear\.d \[r2-128\]
[	 ]+1c8:[	 ]+8121 708a[ 	]+clear\.d \[r2-127\]
[	 ]+1cc:[	 ]+8021 708a[ 	]+clear\.d \[r2-128\]
[	 ]+1d0:[	 ]+5f2d ff00 708a[ 	]+clear\.d \[r2\+255\]
[	 ]+1d6:[	 ]+5f2d 01ff 708a[ 	]+clear\.d \[r2-255\]
[	 ]+1dc:[	 ]+5f2d 01ff 708a[ 	]+clear\.d \[r2-255\]
[	 ]+1e2:[	 ]+5f2d 0001 708a[ 	]+clear\.d \[r2\+256\]
[	 ]+1e8:[	 ]+5f2d 00ff 708a[ 	]+clear\.d \[r2-256\]
[	 ]+1ee:[	 ]+5f2d 68dd 708a[ 	]+clear\.d \[r2-8856\]
[	 ]+1f4:[	 ]+5f2d 00ff 708a[ 	]+clear\.d \[r2-256\]
[	 ]+1fa:[	 ]+5f2d 68dd 708a[ 	]+clear\.d \[r2-8856\]
[	 ]+200:[	 ]+5f2d 9822 708a[ 	]+clear\.d \[r2\+8856\]
[	 ]+206:[	 ]+6f2d ac72 2a00 708a[ 	]+clear\.d \[r2\+(2781868|2a72ac <two701867\+0x13881>)\]
[	 ]+20e:[	 ]+6f2d d5c5 d6ff 708a[ 	]+clear\.d \[r2\+[^]]+\]
[	 ]+216:[	 ]+6f2d acce c09e 708a[ 	]+clear\.d \[r2\+[^]]+\]
[	 ]+21e:[	 ]+6f2d 5331 3f81 708a[ 	]+clear\.d \[r2\+[^]]+\]
[	 ]+226:[	 ]+6f2d 5331 3f81 708a[ 	]+clear\.d \[r2\+[^]]+\]
[	 ]+22e:[	 ]+6f2d b5af 982e 708a[ 	]+clear\.d \[r2\+(0x2e98afb5|2e98afb5 <const_int_m32>)\]
[	 ]+236:[	 ]+6f2d 2b45 941b 708a[ 	]+clear\.d \[r2\+(0x1b94452b|1b94452b <const_int_32>)\]
[	 ]+23e:[	 ]+2a21 708a[ 	]+clear\.d \[r2\+42\]
[	 ]+242:[	 ]+d621 708a[ 	]+clear\.d \[r2-42\]
[	 ]+246:[	 ]+d621 708a[ 	]+clear\.d \[r2-42\]
[	 ]+24a:[	 ]+2a21 708a[ 	]+clear\.d \[r2\+42\]
[	 ]+24e:[	 ]+d621 708a[ 	]+clear\.d \[r2-42\]
[	 ]+252:[	 ]+d621 708a[ 	]+clear\.d \[r2-42\]
[	 ]+256:[	 ]+2a21 708a[ 	]+clear\.d \[r2\+42\]
[	 ]+25a:[	 ]+d621 708a[ 	]+clear\.d \[r2-42\]
[	 ]+25e:[	 ]+2a21 708a[ 	]+clear\.d \[r2\+42\]
[	 ]+262:[	 ]+5f2d ff7f 708a[ 	]+clear\.d \[r2\+32767\]
[	 ]+268:[	 ]+6f2d 0080 0000 708a[ 	]+clear\.d \[r2\+(32768|8000 <three2767\+0x1>)\]
[	 ]+270:[	 ]+6f2d 0180 0000 708a[ 	]+clear\.d \[r2\+(32769|8001 <three2767\+0x2>)\]
[	 ]+278:[	 ]+5f2d 0180 708a[ 	]+clear\.d \[r2-32767\]
[	 ]+27e:[	 ]+5f2d 0080 708a[ 	]+clear\.d \[r2-32768\]
[	 ]+284:[	 ]+6f2d ff7f ffff 708a[ 	]+clear\.d \[r2\+[^]]+\]
[	 ]+28c:[	 ]+5f2d 0180 708a[ 	]+clear\.d \[r2-32767\]
[	 ]+292:[	 ]+5f2d 0080 708a[ 	]+clear\.d \[r2-32768\]
[	 ]+298:[	 ]+6f2d ff7f ffff 708a[ 	]+clear\.d \[r2\+[^]]+\]
[	 ]+2a0:[	 ]+6f2d ffff 0000 708a[ 	]+clear\.d \[r2\+(65535|ffff <six5535>)\]
[	 ]+2a8:[	 ]+6f2d 0000 0100 708a[ 	]+clear\.d \[r2\+(65536|10000 <six5535\+0x1>)\]
[	 ]+2b0:[	 ]+6f2d 2b3a 2900 708a[ 	]+clear\.d \[r2\+(2701867|293a2b <two701867>)\]
[	 ]+2b8:[	 ]+6f2d d5c5 d6ff 708a[ 	]+clear\.d \[r2\+[^]]+\]
[	 ]+2c0:[	 ]+6f2d d5c5 d6ff 708a[ 	]+clear\.d \[r2\+[^]]+\]
[	 ]+2c8:[	 ]+6f2d 0000 0000 708a[ 	]+clear\.d \[r2\+0( <notstart>)?\]
[ 	]+2ca:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+2d0:[	 ]+4205 7c0e[ 	]+clear\.b \[r12=r2\+r0\.b\]
[	 ]+2d4:[	 ]+4255 7c4e[ 	]+clear\.w \[r12=r2\+r5\.b\]
[	 ]+2d8:[	 ]+42a5 7c8e[ 	]+clear\.d \[r12=r2\+r10\.b\]
[	 ]+2dc:[	 ]+4029 7c0e[ 	]+clear\.b \[r12=r2\+\[r0\]\.b\]
[	 ]+2e0:[	 ]+4529 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\]\.b\]
[	 ]+2e4:[	 ]+4a29 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\]\.b\]
[	 ]+2e8:[	 ]+402d 7c0e[ 	]+clear\.b \[r12=r2\+\[r0\+\]\.b\]
[	 ]+2ec:[	 ]+452d 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\+\]\.b\]
[	 ]+2f0:[	 ]+4a2d 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\+\]\.b\]
[	 ]+2f4:[	 ]+452d 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\+\]\.b\]
[	 ]+2f8:[	 ]+4a2d 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\+\]\.b\]
[	 ]+2fc:[	 ]+5205 7c0e[ 	]+clear\.b \[r12=r2\+r0\.w\]
[	 ]+300:[	 ]+5255 7c4e[ 	]+clear\.w \[r12=r2\+r5\.w\]
[	 ]+304:[	 ]+52a5 7c8e[ 	]+clear\.d \[r12=r2\+r10\.w\]
[	 ]+308:[	 ]+5029 7c0e[ 	]+clear\.b \[r12=r2\+\[r0\]\.w\]
[	 ]+30c:[	 ]+5529 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\]\.w\]
[	 ]+310:[	 ]+5a29 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\]\.w\]
[	 ]+314:[	 ]+502d 7c0e[ 	]+clear\.b \[r12=r2\+\[r0\+\]\.w\]
[	 ]+318:[	 ]+552d 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\+\]\.w\]
[	 ]+31c:[	 ]+5a2d 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\+\]\.w\]
[	 ]+320:[	 ]+552d 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\+\]\.w\]
[	 ]+324:[	 ]+5a2d 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\+\]\.w\]
[	 ]+328:[	 ]+6205 7c0e[ 	]+clear\.b \[r12=r2\+r0\.d\]
[	 ]+32c:[	 ]+6255 7c4e[ 	]+clear\.w \[r12=r2\+r5\.d\]
[	 ]+330:[	 ]+62a5 7c8e[ 	]+clear\.d \[r12=r2\+r10\.d\]
[	 ]+334:[	 ]+6029 7c0e[ 	]+clear\.b \[r12=r2\+\[r0\]\.d\]
[	 ]+338:[	 ]+6529 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\]\.d\]
[	 ]+33c:[	 ]+6a29 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\]\.d\]
[	 ]+340:[	 ]+602d 7c0e[ 	]+clear\.b \[r12=r2\+\[r0\+\]\.d\]
[	 ]+344:[	 ]+652d 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\+\]\.d\]
[	 ]+348:[	 ]+6a2d 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\+\]\.d\]
[	 ]+34c:[	 ]+652d 7c4e[ 	]+clear\.w \[r12=r2\+\[r5\+\]\.d\]
[	 ]+350:[	 ]+6a2d 7c8e[ 	]+clear\.d \[r12=r2\+\[r10\+\]\.d\]
[	 ]+354:[	 ]+0021 7c0e[ 	]+clear\.b \[r12=r2\+0\]
[	 ]+358:[	 ]+0121 7c0e[ 	]+clear\.b \[r12=r2\+1\]
[	 ]+35c:[	 ]+7f21 7c0e[ 	]+clear\.b \[r12=r2\+127\]
[	 ]+360:[	 ]+5f2d 8000 7c0e[ 	]+clear\.b \[r12=r2\+128\]
[	 ]+366:[	 ]+ff21 7c0e[ 	]+clear\.b \[r12=r2-1\]
[	 ]+36a:[	 ]+8121 7c0e[ 	]+clear\.b \[r12=r2-127\]
[	 ]+36e:[	 ]+8021 7c0e[ 	]+clear\.b \[r12=r2-128\]
[	 ]+372:[	 ]+5f2d ff00 7c0e[ 	]+clear\.b \[r12=r2\+255\]
[	 ]+378:[	 ]+2a21 7c0e[ 	]+clear\.b \[r12=r2\+42\]
[	 ]+37c:[	 ]+d621 7c0e[ 	]+clear\.b \[r12=r2-42\]
[	 ]+380:[	 ]+d621 7c0e[ 	]+clear\.b \[r12=r2-42\]
[	 ]+384:[	 ]+2a21 7c0e[ 	]+clear\.b \[r12=r2\+42\]
[	 ]+388:[	 ]+d621 7c0e[ 	]+clear\.b \[r12=r2-42\]
[	 ]+38c:[	 ]+d621 7c0e[ 	]+clear\.b \[r12=r2-42\]
[	 ]+390:[	 ]+2a21 7c0e[ 	]+clear\.b \[r12=r2\+42\]
[	 ]+394:[	 ]+d621 7c0e[ 	]+clear\.b \[r12=r2-42\]
[	 ]+398:[	 ]+2a21 7c0e[ 	]+clear\.b \[r12=r2\+42\]
[	 ]+39c:[	 ]+6f2d 0000 0000 7c0e[ 	]+clear\.b \[r12=r2\+0( <notstart>)?\]
[ 	]+39e:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+3a4:[	 ]+0021 7c4e[ 	]+clear\.w \[r12=r2\+0\]
[	 ]+3a8:[	 ]+0121 7c4e[ 	]+clear\.w \[r12=r2\+1\]
[	 ]+3ac:[	 ]+7f21 7c4e[ 	]+clear\.w \[r12=r2\+127\]
[	 ]+3b0:[	 ]+5f2d 8000 7c4e[ 	]+clear\.w \[r12=r2\+128\]
[	 ]+3b6:[	 ]+ff21 7c4e[ 	]+clear\.w \[r12=r2-1\]
[	 ]+3ba:[	 ]+ff21 7c4e[ 	]+clear\.w \[r12=r2-1\]
[	 ]+3be:[	 ]+8121 7c4e[ 	]+clear\.w \[r12=r2-127\]
[	 ]+3c2:[	 ]+8021 7c4e[ 	]+clear\.w \[r12=r2-128\]
[	 ]+3c6:[	 ]+5f2d 7fff 7c4e[ 	]+clear\.w \[r12=r2-129\]
[	 ]+3cc:[	 ]+8121 7c4e[ 	]+clear\.w \[r12=r2-127\]
[	 ]+3d0:[	 ]+8021 7c4e[ 	]+clear\.w \[r12=r2-128\]
[	 ]+3d4:[	 ]+5f2d 7fff 7c4e[ 	]+clear\.w \[r12=r2-129\]
[	 ]+3da:[	 ]+5f2d ff00 7c4e[ 	]+clear\.w \[r12=r2\+255\]
[	 ]+3e0:[	 ]+5f2d 01ff 7c4e[ 	]+clear\.w \[r12=r2-255\]
[	 ]+3e6:[	 ]+5f2d 01ff 7c4e[ 	]+clear\.w \[r12=r2-255\]
[	 ]+3ec:[	 ]+5f2d 0001 7c4e[ 	]+clear\.w \[r12=r2\+256\]
[	 ]+3f2:[	 ]+5f2d 00ff 7c4e[ 	]+clear\.w \[r12=r2-256\]
[	 ]+3f8:[	 ]+5f2d 68dd 7c4e[ 	]+clear\.w \[r12=r2-8856\]
[	 ]+3fe:[	 ]+5f2d 68dd 7c4e[ 	]+clear\.w \[r12=r2-8856\]
[	 ]+404:[	 ]+5f2d 9822 7c4e[ 	]+clear\.w \[r12=r2\+8856\]
[	 ]+40a:[	 ]+2a21 7c4e[ 	]+clear\.w \[r12=r2\+42\]
[	 ]+40e:[	 ]+d621 7c4e[ 	]+clear\.w \[r12=r2-42\]
[	 ]+412:[	 ]+d621 7c4e[ 	]+clear\.w \[r12=r2-42\]
[	 ]+416:[	 ]+2a21 7c4e[ 	]+clear\.w \[r12=r2\+42\]
[	 ]+41a:[	 ]+d621 7c4e[ 	]+clear\.w \[r12=r2-42\]
[	 ]+41e:[	 ]+d621 7c4e[ 	]+clear\.w \[r12=r2-42\]
[	 ]+422:[	 ]+d621 7c4e[ 	]+clear\.w \[r12=r2-42\]
[	 ]+426:[	 ]+2a21 7c4e[ 	]+clear\.w \[r12=r2\+42\]
[	 ]+42a:[	 ]+5f2d ff7f 7c4e[ 	]+clear\.w \[r12=r2\+32767\]
[	 ]+430:[	 ]+6f2d 0080 0000 7c4e[ 	]+clear\.w \[r12=r2\+(32768|8000 <three2767\+0x1>)\]
[	 ]+438:[	 ]+6f2d 0180 0000 7c4e[ 	]+clear\.w \[r12=r2\+(32769|8001 <three2767\+0x2>)\]
[	 ]+440:[	 ]+5f2d 0180 7c4e[ 	]+clear\.w \[r12=r2-32767\]
[	 ]+446:[	 ]+5f2d 0080 7c4e[ 	]+clear\.w \[r12=r2-32768\]
[	 ]+44c:[	 ]+6f2d ff7f ffff 7c4e[ 	]+clear\.w \[r12=r2\+[^]]+\]
[	 ]+454:[	 ]+5f2d 0180 7c4e[ 	]+clear\.w \[r12=r2-32767\]
[	 ]+45a:[	 ]+5f2d 0080 7c4e[ 	]+clear\.w \[r12=r2-32768\]
[	 ]+460:[	 ]+6f2d ff7f ffff 7c4e[ 	]+clear\.w \[r12=r2\+[^]]+\]
[	 ]+468:[	 ]+6f2d ffff 0000 7c4e[ 	]+clear\.w \[r12=r2\+(65535|ffff <six5535>)\]
[	 ]+470:[	 ]+6f2d 0000 0000 7c4e[ 	]+clear\.w \[r12=r2\+0( <notstart>)?\]
[ 	]+472:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+478:[	 ]+0021 7c8e[ 	]+clear\.d \[r12=r2\+0\]
[	 ]+47c:[	 ]+0121 7c8e[ 	]+clear\.d \[r12=r2\+1\]
[	 ]+480:[	 ]+7f21 7c8e[ 	]+clear\.d \[r12=r2\+127\]
[	 ]+484:[	 ]+5f2d 8000 7c8e[ 	]+clear\.d \[r12=r2\+128\]
[	 ]+48a:[	 ]+ff21 7c8e[ 	]+clear\.d \[r12=r2-1\]
[	 ]+48e:[	 ]+ff21 7c8e[ 	]+clear\.d \[r12=r2-1\]
[	 ]+492:[	 ]+8121 7c8e[ 	]+clear\.d \[r12=r2-127\]
[	 ]+496:[	 ]+8021 7c8e[ 	]+clear\.d \[r12=r2-128\]
[	 ]+49a:[	 ]+8121 7c8e[ 	]+clear\.d \[r12=r2-127\]
[	 ]+49e:[	 ]+8021 7c8e[ 	]+clear\.d \[r12=r2-128\]
[	 ]+4a2:[	 ]+5f2d ff00 7c8e[ 	]+clear\.d \[r12=r2\+255\]
[	 ]+4a8:[	 ]+5f2d 01ff 7c8e[ 	]+clear\.d \[r12=r2-255\]
[	 ]+4ae:[	 ]+5f2d 01ff 7c8e[ 	]+clear\.d \[r12=r2-255\]
[	 ]+4b4:[	 ]+5f2d 0001 7c8e[ 	]+clear\.d \[r12=r2\+256\]
[	 ]+4ba:[	 ]+5f2d 00ff 7c8e[ 	]+clear\.d \[r12=r2-256\]
[	 ]+4c0:[	 ]+5f2d 68dd 7c8e[ 	]+clear\.d \[r12=r2-8856\]
[	 ]+4c6:[	 ]+5f2d 00ff 7c8e[ 	]+clear\.d \[r12=r2-256\]
[	 ]+4cc:[	 ]+5f2d 68dd 7c8e[ 	]+clear\.d \[r12=r2-8856\]
[	 ]+4d2:[	 ]+5f2d 9822 7c8e[ 	]+clear\.d \[r12=r2\+8856\]
[	 ]+4d8:[	 ]+6f2d ac72 2a00 7c8e[ 	]+clear\.d \[r12=r2\+(2781868|2a72ac <two701867\+0x13881>)\]
[	 ]+4e0:[	 ]+6f2d d5c5 d6ff 7c8e[ 	]+clear\.d \[r12=r2\+[^]]+\]
[	 ]+4e8:[	 ]+6f2d acce c09e 7c8e[ 	]+clear\.d \[r12=r2\+[^]]+\]
[	 ]+4f0:[	 ]+6f2d 5331 3f81 7c8e[ 	]+clear\.d \[r12=r2\+[^]]+\]
[	 ]+4f8:[	 ]+6f2d 5331 3f81 7c8e[ 	]+clear\.d \[r12=r2\+[^]]+\]
[	 ]+500:[	 ]+6f2d b5af 982e 7c8e[ 	]+clear\.d \[r12=r2\+(0x2e98afb5|2e98afb5 <const_int_m32>)\]
[	 ]+508:[	 ]+6f2d 2b45 941b 7c8e[ 	]+clear\.d \[r12=r2\+(0x1b94452b|1b94452b <const_int_32>)\]
[	 ]+510:[	 ]+2a21 7c8e[ 	]+clear\.d \[r12=r2\+42\]
[	 ]+514:[	 ]+d621 7c8e[ 	]+clear\.d \[r12=r2-42\]
[	 ]+518:[	 ]+d621 7c8e[ 	]+clear\.d \[r12=r2-42\]
[	 ]+51c:[	 ]+2a21 7c8e[ 	]+clear\.d \[r12=r2\+42\]
[	 ]+520:[	 ]+d621 7c8e[ 	]+clear\.d \[r12=r2-42\]
[	 ]+524:[	 ]+d621 7c8e[ 	]+clear\.d \[r12=r2-42\]
[	 ]+528:[	 ]+2a21 7c8e[ 	]+clear\.d \[r12=r2\+42\]
[	 ]+52c:[	 ]+d621 7c8e[ 	]+clear\.d \[r12=r2-42\]
[	 ]+530:[	 ]+2a21 7c8e[ 	]+clear\.d \[r12=r2\+42\]
[	 ]+534:[	 ]+5f2d ff7f 7c8e[ 	]+clear\.d \[r12=r2\+32767\]
[	 ]+53a:[	 ]+6f2d 0080 0000 7c8e[ 	]+clear\.d \[r12=r2\+(32768|8000 <three2767\+0x1>)\]
[	 ]+542:[	 ]+6f2d 0180 0000 7c8e[ 	]+clear\.d \[r12=r2\+(32769|8001 <three2767\+0x2>)\]
[	 ]+54a:[	 ]+5f2d 0180 7c8e[ 	]+clear\.d \[r12=r2-32767\]
[	 ]+550:[	 ]+5f2d 0080 7c8e[ 	]+clear\.d \[r12=r2-32768\]
[	 ]+556:[	 ]+6f2d ff7f ffff 7c8e[ 	]+clear\.d \[r12=r2\+[^]]+\]
[	 ]+55e:[	 ]+5f2d 0180 7c8e[ 	]+clear\.d \[r12=r2-32767\]
[	 ]+564:[	 ]+5f2d 0080 7c8e[ 	]+clear\.d \[r12=r2-32768\]
[	 ]+56a:[	 ]+6f2d ff7f ffff 7c8e[ 	]+clear\.d \[r12=r2\+[^]]+\]
[	 ]+572:[	 ]+6f2d ffff 0000 7c8e[ 	]+clear\.d \[r12=r2\+(65535|ffff <six5535>)\]
[	 ]+57a:[	 ]+6f2d 0000 0100 7c8e[ 	]+clear\.d \[r12=r2\+(65536|10000 <six5535\+0x1>)\]
[	 ]+582:[	 ]+6f2d 2b3a 2900 7c8e[ 	]+clear\.d \[r12=r2\+(2701867|293a2b <two701867>)\]
[	 ]+58a:[	 ]+6f2d d5c5 d6ff 7c8e[ 	]+clear\.d \[r12=r2\+[^]]+\]
[	 ]+592:[	 ]+6f2d d5c5 d6ff 7c8e[ 	]+clear\.d \[r12=r2\+[^]]+\]
[	 ]+59a:[	 ]+6f2d 0000 0000 7c8e[ 	]+clear\.d \[r12=r2\+0( <notstart>)?\]
[ 	]+59c:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+5a2:[	 ]+7309 700a[ 	]+clear\.b \[\[r3\]\]
[	 ]+5a6:[	 ]+7209 704a[ 	]+clear\.w \[\[r2\]\]
[	 ]+5aa:[	 ]+7309 708a[ 	]+clear\.d \[\[r3\]\]
[	 ]+5ae:[	 ]+790d 700a[ 	]+clear\.b \[\[r9\+\]\]
[	 ]+5b2:[	 ]+730d 704a[ 	]+clear\.w \[\[r3\+\]\]
[	 ]+5b6:[	 ]+710d 708a[ 	]+clear\.d \[\[r1\+\]\]
[	 ]+5ba:[	 ]+7f0d 0000 0000 700a[ 	]+clear\.b \[(0x0|0 <notstart>)\]
[ 	]+5bc:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+5c2:[	 ]+7f0d 0000 0000 704a[ 	]+clear\.w \[(0x0|0 <notstart>)\]
[ 	]+5c4:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+5ca:[	 ]+7f0d 0000 0000 708a[ 	]+clear\.d \[(0x0|0 <notstart>)\]
[ 	]+5cc:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+5d2:[	 ]+7f0d 0000 0000 700a[ 	]+clear\.b \[(0x0|0 <notstart>)\]
[ 	]+5d4:[ 	]+(R_CRIS_)?32[ 	]+\.text
[	 ]+5da:[	 ]+7f0d 0000 0000 704a[ 	]+clear\.w \[(0x0|0 <notstart>)\]
[ 	]+5dc:[ 	]+(R_CRIS_)?32[ 	]+\.text
[	 ]+5e2:[	 ]+7f0d 0000 0000 708a[ 	]+clear\.d \[(0x0|0 <notstart>)\]
[ 	]+5e4:[ 	]+(R_CRIS_)?32[ 	]+\.text

0+5ea <end>:
	\.\.\.
