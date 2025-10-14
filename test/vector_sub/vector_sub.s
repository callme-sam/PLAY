TARGET IS FABRIC CONTROLLER
riscv32-unknown-elf-objdump -Mmarch=rv32imcxgap9 -d /home/sam/repos/PLAY/test/vector_sub/BUILD/PULP/GCC_RISCV//vector-sub-test/vector-sub-test

/home/sam/repos/PLAY/test/vector_sub/BUILD/PULP/GCC_RISCV//vector-sub-test/vector-sub-test:     file format elf32-littleriscv


Disassembly of section .vectors:

1c008000 <__irq_vector_base>:
1c008000:	08c0006f          	j	1c00808c <pos_illegal_instr>
1c008004:	08c0006f          	j	1c008090 <pos_no_irq_handler>
1c008008:	0880006f          	j	1c008090 <pos_no_irq_handler>
1c00800c:	0840006f          	j	1c008090 <pos_no_irq_handler>
1c008010:	0800006f          	j	1c008090 <pos_no_irq_handler>
1c008014:	07c0006f          	j	1c008090 <pos_no_irq_handler>
1c008018:	0780006f          	j	1c008090 <pos_no_irq_handler>
1c00801c:	0740006f          	j	1c008090 <pos_no_irq_handler>
1c008020:	0700006f          	j	1c008090 <pos_no_irq_handler>
1c008024:	06c0006f          	j	1c008090 <pos_no_irq_handler>
1c008028:	0680006f          	j	1c008090 <pos_no_irq_handler>
1c00802c:	0640006f          	j	1c008090 <pos_no_irq_handler>
1c008030:	0600006f          	j	1c008090 <pos_no_irq_handler>
1c008034:	05c0006f          	j	1c008090 <pos_no_irq_handler>
1c008038:	0580006f          	j	1c008090 <pos_no_irq_handler>
1c00803c:	0540006f          	j	1c008090 <pos_no_irq_handler>
1c008040:	0500006f          	j	1c008090 <pos_no_irq_handler>
1c008044:	04c0006f          	j	1c008090 <pos_no_irq_handler>
1c008048:	0480006f          	j	1c008090 <pos_no_irq_handler>
1c00804c:	0440006f          	j	1c008090 <pos_no_irq_handler>
1c008050:	0400006f          	j	1c008090 <pos_no_irq_handler>
1c008054:	03c0006f          	j	1c008090 <pos_no_irq_handler>
1c008058:	0380006f          	j	1c008090 <pos_no_irq_handler>
1c00805c:	0340006f          	j	1c008090 <pos_no_irq_handler>
1c008060:	0300006f          	j	1c008090 <pos_no_irq_handler>
1c008064:	02c0006f          	j	1c008090 <pos_no_irq_handler>
1c008068:	0280006f          	j	1c008090 <pos_no_irq_handler>
1c00806c:	0240006f          	j	1c008090 <pos_no_irq_handler>
1c008070:	0200006f          	j	1c008090 <pos_no_irq_handler>
1c008074:	01c0006f          	j	1c008090 <pos_no_irq_handler>
1c008078:	0180006f          	j	1c008090 <pos_no_irq_handler>
1c00807c:	0140006f          	j	1c008090 <pos_no_irq_handler>

1c008080 <_start>:
1c008080:	00003517          	auipc	a0,0x3
1c008084:	41e50513          	addi	a0,a0,1054 # 1c00b49e <pos_init_entry>
1c008088:	00050067          	jr	a0

1c00808c <pos_illegal_instr>:
1c00808c:	0000006f          	j	1c00808c <pos_illegal_instr>

1c008090 <pos_no_irq_handler>:
1c008090:	30200073          	mret

1c008094 <pos_semihosting_call>:
1c008094:	00100073          	ebreak
1c008098:	00008067          	ret

Disassembly of section .text:

1c00809c <__udivdi3>:
1c00809c:	87b2                	mv	a5,a2
1c00809e:	8736                	mv	a4,a3
1c0080a0:	88aa                	mv	a7,a0
1c0080a2:	882e                	mv	a6,a1
1c0080a4:	1e069d63          	bnez	a3,1c00829e <__udivdi3+0x202>
1c0080a8:	1c001337          	lui	t1,0x1c001
1c0080ac:	86830313          	addi	t1,t1,-1944 # 1c000868 <__DTOR_END__>
1c0080b0:	0ac5fd63          	bleu	a2,a1,1c00816a <__udivdi3+0xce>
1c0080b4:	6741                	lui	a4,0x10
1c0080b6:	0ae67363          	bleu	a4,a2,1c00815c <__udivdi3+0xc0>
1c0080ba:	0ff00693          	li	a3,255
1c0080be:	00c6b6b3          	sltu	a3,a3,a2
1c0080c2:	068e                	slli	a3,a3,0x3
1c0080c4:	00d65733          	srl	a4,a2,a3
1c0080c8:	933a                	add	t1,t1,a4
1c0080ca:	00034703          	lbu	a4,0(t1)
1c0080ce:	02000313          	li	t1,32
1c0080d2:	96ba                	add	a3,a3,a4
1c0080d4:	40d30333          	sub	t1,t1,a3
1c0080d8:	00030c63          	beqz	t1,1c0080f0 <__udivdi3+0x54>
1c0080dc:	00659733          	sll	a4,a1,t1
1c0080e0:	00d556b3          	srl	a3,a0,a3
1c0080e4:	006617b3          	sll	a5,a2,t1
1c0080e8:	00e6e833          	or	a6,a3,a4
1c0080ec:	006518b3          	sll	a7,a0,t1
1c0080f0:	0107d513          	srli	a0,a5,0x10
1c0080f4:	02a87633          	remu	a2,a6,a0
1c0080f8:	02a85733          	divu	a4,a6,a0
1c0080fc:	0642                	slli	a2,a2,0x10
1c0080fe:	1007d5b3          	p.exthz	a1,a5
1c008102:	0108d693          	srli	a3,a7,0x10
1c008106:	8ed1                	or	a3,a3,a2
1c008108:	02e58833          	mul	a6,a1,a4
1c00810c:	863a                	mv	a2,a4
1c00810e:	0106fc63          	bleu	a6,a3,1c008126 <__udivdi3+0x8a>
1c008112:	96be                	add	a3,a3,a5
1c008114:	fff70613          	addi	a2,a4,-1 # ffff <__l1_heap_size+0x2f>
1c008118:	00f6e763          	bltu	a3,a5,1c008126 <__udivdi3+0x8a>
1c00811c:	0106f563          	bleu	a6,a3,1c008126 <__udivdi3+0x8a>
1c008120:	ffe70613          	addi	a2,a4,-2
1c008124:	96be                	add	a3,a3,a5
1c008126:	410686b3          	sub	a3,a3,a6
1c00812a:	02a6f833          	remu	a6,a3,a0
1c00812e:	02a6d6b3          	divu	a3,a3,a0
1c008132:	df0828b3          	p.insert	a7,a6,15,16
1c008136:	02d58733          	mul	a4,a1,a3
1c00813a:	8536                	mv	a0,a3
1c00813c:	00e8fb63          	bleu	a4,a7,1c008152 <__udivdi3+0xb6>
1c008140:	98be                	add	a7,a7,a5
1c008142:	fff68513          	addi	a0,a3,-1
1c008146:	00f8e663          	bltu	a7,a5,1c008152 <__udivdi3+0xb6>
1c00814a:	00e8f463          	bleu	a4,a7,1c008152 <__udivdi3+0xb6>
1c00814e:	ffe68513          	addi	a0,a3,-2
1c008152:	01061793          	slli	a5,a2,0x10
1c008156:	8fc9                	or	a5,a5,a0
1c008158:	4801                	li	a6,0
1c00815a:	a06d                	j	1c008204 <__udivdi3+0x168>
1c00815c:	01000737          	lui	a4,0x1000
1c008160:	46c1                	li	a3,16
1c008162:	f6e661e3          	bltu	a2,a4,1c0080c4 <__udivdi3+0x28>
1c008166:	46e1                	li	a3,24
1c008168:	bfb1                	j	1c0080c4 <__udivdi3+0x28>
1c00816a:	e601                	bnez	a2,1c008172 <__udivdi3+0xd6>
1c00816c:	4685                	li	a3,1
1c00816e:	02c6d7b3          	divu	a5,a3,a2
1c008172:	66c1                	lui	a3,0x10
1c008174:	08d7fb63          	bleu	a3,a5,1c00820a <__udivdi3+0x16e>
1c008178:	0ff00693          	li	a3,255
1c00817c:	00f6f363          	bleu	a5,a3,1c008182 <__udivdi3+0xe6>
1c008180:	4721                	li	a4,8
1c008182:	00e7d6b3          	srl	a3,a5,a4
1c008186:	9336                	add	t1,t1,a3
1c008188:	00034683          	lbu	a3,0(t1)
1c00818c:	02000613          	li	a2,32
1c008190:	96ba                	add	a3,a3,a4
1c008192:	8e15                	sub	a2,a2,a3
1c008194:	e251                	bnez	a2,1c008218 <__udivdi3+0x17c>
1c008196:	40f58733          	sub	a4,a1,a5
1c00819a:	4805                	li	a6,1
1c00819c:	0107d513          	srli	a0,a5,0x10
1c0081a0:	02a77633          	remu	a2,a4,a0
1c0081a4:	02a75733          	divu	a4,a4,a0
1c0081a8:	0642                	slli	a2,a2,0x10
1c0081aa:	1007d5b3          	p.exthz	a1,a5
1c0081ae:	0108d693          	srli	a3,a7,0x10
1c0081b2:	8ed1                	or	a3,a3,a2
1c0081b4:	02e58333          	mul	t1,a1,a4
1c0081b8:	863a                	mv	a2,a4
1c0081ba:	0066fc63          	bleu	t1,a3,1c0081d2 <__udivdi3+0x136>
1c0081be:	96be                	add	a3,a3,a5
1c0081c0:	fff70613          	addi	a2,a4,-1 # ffffff <__l1_heap_size+0xff002f>
1c0081c4:	00f6e763          	bltu	a3,a5,1c0081d2 <__udivdi3+0x136>
1c0081c8:	0066f563          	bleu	t1,a3,1c0081d2 <__udivdi3+0x136>
1c0081cc:	ffe70613          	addi	a2,a4,-2
1c0081d0:	96be                	add	a3,a3,a5
1c0081d2:	406686b3          	sub	a3,a3,t1
1c0081d6:	02a6f333          	remu	t1,a3,a0
1c0081da:	02a6d6b3          	divu	a3,a3,a0
1c0081de:	df0328b3          	p.insert	a7,t1,15,16
1c0081e2:	02d58733          	mul	a4,a1,a3
1c0081e6:	8536                	mv	a0,a3
1c0081e8:	00e8fb63          	bleu	a4,a7,1c0081fe <__udivdi3+0x162>
1c0081ec:	98be                	add	a7,a7,a5
1c0081ee:	fff68513          	addi	a0,a3,-1 # ffff <__l1_heap_size+0x2f>
1c0081f2:	00f8e663          	bltu	a7,a5,1c0081fe <__udivdi3+0x162>
1c0081f6:	00e8f463          	bleu	a4,a7,1c0081fe <__udivdi3+0x162>
1c0081fa:	ffe68513          	addi	a0,a3,-2
1c0081fe:	01061793          	slli	a5,a2,0x10
1c008202:	8fc9                	or	a5,a5,a0
1c008204:	853e                	mv	a0,a5
1c008206:	85c2                	mv	a1,a6
1c008208:	8082                	ret
1c00820a:	010006b7          	lui	a3,0x1000
1c00820e:	4741                	li	a4,16
1c008210:	f6d7e9e3          	bltu	a5,a3,1c008182 <__udivdi3+0xe6>
1c008214:	4761                	li	a4,24
1c008216:	b7b5                	j	1c008182 <__udivdi3+0xe6>
1c008218:	00c797b3          	sll	a5,a5,a2
1c00821c:	00d5d333          	srl	t1,a1,a3
1c008220:	0107de13          	srli	t3,a5,0x10
1c008224:	00c59733          	sll	a4,a1,a2
1c008228:	00c518b3          	sll	a7,a0,a2
1c00822c:	03c37633          	remu	a2,t1,t3
1c008230:	00d555b3          	srl	a1,a0,a3
1c008234:	03c35533          	divu	a0,t1,t3
1c008238:	8dd9                	or	a1,a1,a4
1c00823a:	0642                	slli	a2,a2,0x10
1c00823c:	1007d733          	p.exthz	a4,a5
1c008240:	0105d693          	srli	a3,a1,0x10
1c008244:	02a70333          	mul	t1,a4,a0
1c008248:	8ed1                	or	a3,a3,a2
1c00824a:	882a                	mv	a6,a0
1c00824c:	0066fc63          	bleu	t1,a3,1c008264 <__udivdi3+0x1c8>
1c008250:	96be                	add	a3,a3,a5
1c008252:	fff50813          	addi	a6,a0,-1
1c008256:	00f6e763          	bltu	a3,a5,1c008264 <__udivdi3+0x1c8>
1c00825a:	0066f563          	bleu	t1,a3,1c008264 <__udivdi3+0x1c8>
1c00825e:	ffe50813          	addi	a6,a0,-2
1c008262:	96be                	add	a3,a3,a5
1c008264:	406686b3          	sub	a3,a3,t1
1c008268:	03c6f633          	remu	a2,a3,t3
1c00826c:	03c6d6b3          	divu	a3,a3,t3
1c008270:	df0625b3          	p.insert	a1,a2,15,16
1c008274:	02d70733          	mul	a4,a4,a3
1c008278:	8636                	mv	a2,a3
1c00827a:	00e5fc63          	bleu	a4,a1,1c008292 <__udivdi3+0x1f6>
1c00827e:	95be                	add	a1,a1,a5
1c008280:	fff68613          	addi	a2,a3,-1 # ffffff <__l1_heap_size+0xff002f>
1c008284:	00f5e763          	bltu	a1,a5,1c008292 <__udivdi3+0x1f6>
1c008288:	00e5f563          	bleu	a4,a1,1c008292 <__udivdi3+0x1f6>
1c00828c:	ffe68613          	addi	a2,a3,-2
1c008290:	95be                	add	a1,a1,a5
1c008292:	0842                	slli	a6,a6,0x10
1c008294:	40e58733          	sub	a4,a1,a4
1c008298:	00c86833          	or	a6,a6,a2
1c00829c:	b701                	j	1c00819c <__udivdi3+0x100>
1c00829e:	12d5ea63          	bltu	a1,a3,1c0083d2 <__udivdi3+0x336>
1c0082a2:	67c1                	lui	a5,0x10
1c0082a4:	02f6fd63          	bleu	a5,a3,1c0082de <__udivdi3+0x242>
1c0082a8:	0ff00793          	li	a5,255
1c0082ac:	00d7b8b3          	sltu	a7,a5,a3
1c0082b0:	088e                	slli	a7,a7,0x3
1c0082b2:	1c001737          	lui	a4,0x1c001
1c0082b6:	0116d7b3          	srl	a5,a3,a7
1c0082ba:	86870713          	addi	a4,a4,-1944 # 1c000868 <__DTOR_END__>
1c0082be:	97ba                	add	a5,a5,a4
1c0082c0:	0007c783          	lbu	a5,0(a5) # 10000 <__l1_heap_size+0x30>
1c0082c4:	02000813          	li	a6,32
1c0082c8:	97c6                	add	a5,a5,a7
1c0082ca:	40f80833          	sub	a6,a6,a5
1c0082ce:	00081f63          	bnez	a6,1c0082ec <__udivdi3+0x250>
1c0082d2:	4785                	li	a5,1
1c0082d4:	f2b6e8e3          	bltu	a3,a1,1c008204 <__udivdi3+0x168>
1c0082d8:	04a637b3          	p.sletu	a5,a2,a0
1c0082dc:	b725                	j	1c008204 <__udivdi3+0x168>
1c0082de:	010007b7          	lui	a5,0x1000
1c0082e2:	48c1                	li	a7,16
1c0082e4:	fcf6e7e3          	bltu	a3,a5,1c0082b2 <__udivdi3+0x216>
1c0082e8:	48e1                	li	a7,24
1c0082ea:	b7e1                	j	1c0082b2 <__udivdi3+0x216>
1c0082ec:	00f658b3          	srl	a7,a2,a5
1c0082f0:	010696b3          	sll	a3,a3,a6
1c0082f4:	00d8e6b3          	or	a3,a7,a3
1c0082f8:	00f5d333          	srl	t1,a1,a5
1c0082fc:	0106de13          	srli	t3,a3,0x10
1c008300:	00f55733          	srl	a4,a0,a5
1c008304:	03c377b3          	remu	a5,t1,t3
1c008308:	010595b3          	sll	a1,a1,a6
1c00830c:	03c35333          	divu	t1,t1,t3
1c008310:	8f4d                	or	a4,a4,a1
1c008312:	07c2                	slli	a5,a5,0x10
1c008314:	1006d8b3          	p.exthz	a7,a3
1c008318:	01075593          	srli	a1,a4,0x10
1c00831c:	8ddd                	or	a1,a1,a5
1c00831e:	02688eb3          	mul	t4,a7,t1
1c008322:	01061633          	sll	a2,a2,a6
1c008326:	879a                	mv	a5,t1
1c008328:	01d5fc63          	bleu	t4,a1,1c008340 <__udivdi3+0x2a4>
1c00832c:	95b6                	add	a1,a1,a3
1c00832e:	fff30793          	addi	a5,t1,-1
1c008332:	00d5e763          	bltu	a1,a3,1c008340 <__udivdi3+0x2a4>
1c008336:	01d5f563          	bleu	t4,a1,1c008340 <__udivdi3+0x2a4>
1c00833a:	ffe30793          	addi	a5,t1,-2
1c00833e:	95b6                	add	a1,a1,a3
1c008340:	41d585b3          	sub	a1,a1,t4
1c008344:	03c5f333          	remu	t1,a1,t3
1c008348:	03c5d5b3          	divu	a1,a1,t3
1c00834c:	df032733          	p.insert	a4,t1,15,16
1c008350:	02b888b3          	mul	a7,a7,a1
1c008354:	832e                	mv	t1,a1
1c008356:	01177c63          	bleu	a7,a4,1c00836e <__udivdi3+0x2d2>
1c00835a:	9736                	add	a4,a4,a3
1c00835c:	fff58313          	addi	t1,a1,-1
1c008360:	00d76763          	bltu	a4,a3,1c00836e <__udivdi3+0x2d2>
1c008364:	01177563          	bleu	a7,a4,1c00836e <__udivdi3+0x2d2>
1c008368:	ffe58313          	addi	t1,a1,-2
1c00836c:	9736                	add	a4,a4,a3
1c00836e:	07c2                	slli	a5,a5,0x10
1c008370:	6e41                	lui	t3,0x10
1c008372:	0067e7b3          	or	a5,a5,t1
1c008376:	fffe0593          	addi	a1,t3,-1 # ffff <__l1_heap_size+0x2f>
1c00837a:	00b7f6b3          	and	a3,a5,a1
1c00837e:	41170733          	sub	a4,a4,a7
1c008382:	8df1                	and	a1,a1,a2
1c008384:	0107d893          	srli	a7,a5,0x10
1c008388:	02b68333          	mul	t1,a3,a1
1c00838c:	02b885b3          	mul	a1,a7,a1
1c008390:	8241                	srli	a2,a2,0x10
1c008392:	8eae                	mv	t4,a1
1c008394:	42c68eb3          	p.mac	t4,a3,a2
1c008398:	01035693          	srli	a3,t1,0x10
1c00839c:	96f6                	add	a3,a3,t4
1c00839e:	02c888b3          	mul	a7,a7,a2
1c0083a2:	00b6f363          	bleu	a1,a3,1c0083a8 <__udivdi3+0x30c>
1c0083a6:	98f2                	add	a7,a7,t3
1c0083a8:	0106d613          	srli	a2,a3,0x10
1c0083ac:	98b2                	add	a7,a7,a2
1c0083ae:	03176063          	bltu	a4,a7,1c0083ce <__udivdi3+0x332>
1c0083b2:	db1713e3          	bne	a4,a7,1c008158 <__udivdi3+0xbc>
1c0083b6:	6741                	lui	a4,0x10
1c0083b8:	177d                	addi	a4,a4,-1
1c0083ba:	8ef9                	and	a3,a3,a4
1c0083bc:	06c2                	slli	a3,a3,0x10
1c0083be:	00e37333          	and	t1,t1,a4
1c0083c2:	01051533          	sll	a0,a0,a6
1c0083c6:	969a                	add	a3,a3,t1
1c0083c8:	4801                	li	a6,0
1c0083ca:	e2d57de3          	bleu	a3,a0,1c008204 <__udivdi3+0x168>
1c0083ce:	17fd                	addi	a5,a5,-1
1c0083d0:	b361                	j	1c008158 <__udivdi3+0xbc>
1c0083d2:	4801                	li	a6,0
1c0083d4:	4781                	li	a5,0
1c0083d6:	b53d                	j	1c008204 <__udivdi3+0x168>

1c0083d8 <__umoddi3>:
1c0083d8:	88b2                	mv	a7,a2
1c0083da:	8736                	mv	a4,a3
1c0083dc:	87aa                	mv	a5,a0
1c0083de:	882e                	mv	a6,a1
1c0083e0:	1a069963          	bnez	a3,1c008592 <__umoddi3+0x1ba>
1c0083e4:	1c0016b7          	lui	a3,0x1c001
1c0083e8:	86868693          	addi	a3,a3,-1944 # 1c000868 <__DTOR_END__>
1c0083ec:	0ac5f463          	bleu	a2,a1,1c008494 <__umoddi3+0xbc>
1c0083f0:	6341                	lui	t1,0x10
1c0083f2:	08667a63          	bleu	t1,a2,1c008486 <__umoddi3+0xae>
1c0083f6:	0ff00313          	li	t1,255
1c0083fa:	00c37363          	bleu	a2,t1,1c008400 <__umoddi3+0x28>
1c0083fe:	4721                	li	a4,8
1c008400:	00e65333          	srl	t1,a2,a4
1c008404:	969a                	add	a3,a3,t1
1c008406:	0006c683          	lbu	a3,0(a3)
1c00840a:	02000313          	li	t1,32
1c00840e:	9736                	add	a4,a4,a3
1c008410:	40e30333          	sub	t1,t1,a4
1c008414:	00030c63          	beqz	t1,1c00842c <__umoddi3+0x54>
1c008418:	006595b3          	sll	a1,a1,t1
1c00841c:	00e55733          	srl	a4,a0,a4
1c008420:	006618b3          	sll	a7,a2,t1
1c008424:	00b76833          	or	a6,a4,a1
1c008428:	006517b3          	sll	a5,a0,t1
1c00842c:	0108d613          	srli	a2,a7,0x10
1c008430:	02c87733          	remu	a4,a6,a2
1c008434:	02c85833          	divu	a6,a6,a2
1c008438:	1008d533          	p.exthz	a0,a7
1c00843c:	0742                	slli	a4,a4,0x10
1c00843e:	0107d693          	srli	a3,a5,0x10
1c008442:	03050833          	mul	a6,a0,a6
1c008446:	8ed9                	or	a3,a3,a4
1c008448:	0106f863          	bleu	a6,a3,1c008458 <__umoddi3+0x80>
1c00844c:	96c6                	add	a3,a3,a7
1c00844e:	0116e563          	bltu	a3,a7,1c008458 <__umoddi3+0x80>
1c008452:	0106f363          	bleu	a6,a3,1c008458 <__umoddi3+0x80>
1c008456:	96c6                	add	a3,a3,a7
1c008458:	410686b3          	sub	a3,a3,a6
1c00845c:	02c6f733          	remu	a4,a3,a2
1c008460:	02c6d6b3          	divu	a3,a3,a2
1c008464:	df0727b3          	p.insert	a5,a4,15,16
1c008468:	02d506b3          	mul	a3,a0,a3
1c00846c:	00d7f863          	bleu	a3,a5,1c00847c <__umoddi3+0xa4>
1c008470:	97c6                	add	a5,a5,a7
1c008472:	0117e563          	bltu	a5,a7,1c00847c <__umoddi3+0xa4>
1c008476:	00d7f363          	bleu	a3,a5,1c00847c <__umoddi3+0xa4>
1c00847a:	97c6                	add	a5,a5,a7
1c00847c:	8f95                	sub	a5,a5,a3
1c00847e:	0067d533          	srl	a0,a5,t1
1c008482:	4581                	li	a1,0
1c008484:	8082                	ret
1c008486:	01000337          	lui	t1,0x1000
1c00848a:	4741                	li	a4,16
1c00848c:	f6666ae3          	bltu	a2,t1,1c008400 <__umoddi3+0x28>
1c008490:	4761                	li	a4,24
1c008492:	b7bd                	j	1c008400 <__umoddi3+0x28>
1c008494:	e601                	bnez	a2,1c00849c <__umoddi3+0xc4>
1c008496:	4605                	li	a2,1
1c008498:	031658b3          	divu	a7,a2,a7
1c00849c:	6641                	lui	a2,0x10
1c00849e:	06c8ff63          	bleu	a2,a7,1c00851c <__umoddi3+0x144>
1c0084a2:	0ff00613          	li	a2,255
1c0084a6:	01167363          	bleu	a7,a2,1c0084ac <__umoddi3+0xd4>
1c0084aa:	4721                	li	a4,8
1c0084ac:	00e8d633          	srl	a2,a7,a4
1c0084b0:	96b2                	add	a3,a3,a2
1c0084b2:	0006c603          	lbu	a2,0(a3)
1c0084b6:	02000313          	li	t1,32
1c0084ba:	963a                	add	a2,a2,a4
1c0084bc:	40c30333          	sub	t1,t1,a2
1c0084c0:	06031563          	bnez	t1,1c00852a <__umoddi3+0x152>
1c0084c4:	411585b3          	sub	a1,a1,a7
1c0084c8:	0108d713          	srli	a4,a7,0x10
1c0084cc:	02e5f6b3          	remu	a3,a1,a4
1c0084d0:	02e5d5b3          	divu	a1,a1,a4
1c0084d4:	1008d533          	p.exthz	a0,a7
1c0084d8:	06c2                	slli	a3,a3,0x10
1c0084da:	0107d613          	srli	a2,a5,0x10
1c0084de:	02b505b3          	mul	a1,a0,a1
1c0084e2:	8ed1                	or	a3,a3,a2
1c0084e4:	00b6f863          	bleu	a1,a3,1c0084f4 <__umoddi3+0x11c>
1c0084e8:	96c6                	add	a3,a3,a7
1c0084ea:	0116e563          	bltu	a3,a7,1c0084f4 <__umoddi3+0x11c>
1c0084ee:	00b6f363          	bleu	a1,a3,1c0084f4 <__umoddi3+0x11c>
1c0084f2:	96c6                	add	a3,a3,a7
1c0084f4:	40b685b3          	sub	a1,a3,a1
1c0084f8:	02e5f6b3          	remu	a3,a1,a4
1c0084fc:	02e5d5b3          	divu	a1,a1,a4
1c008500:	df06a7b3          	p.insert	a5,a3,15,16
1c008504:	02b505b3          	mul	a1,a0,a1
1c008508:	00b7f863          	bleu	a1,a5,1c008518 <__umoddi3+0x140>
1c00850c:	97c6                	add	a5,a5,a7
1c00850e:	0117e563          	bltu	a5,a7,1c008518 <__umoddi3+0x140>
1c008512:	00b7f363          	bleu	a1,a5,1c008518 <__umoddi3+0x140>
1c008516:	97c6                	add	a5,a5,a7
1c008518:	8f8d                	sub	a5,a5,a1
1c00851a:	b795                	j	1c00847e <__umoddi3+0xa6>
1c00851c:	01000637          	lui	a2,0x1000
1c008520:	4741                	li	a4,16
1c008522:	f8c8e5e3          	bltu	a7,a2,1c0084ac <__umoddi3+0xd4>
1c008526:	4761                	li	a4,24
1c008528:	b751                	j	1c0084ac <__umoddi3+0xd4>
1c00852a:	006898b3          	sll	a7,a7,t1
1c00852e:	00c5d733          	srl	a4,a1,a2
1c008532:	006517b3          	sll	a5,a0,t1
1c008536:	00c55633          	srl	a2,a0,a2
1c00853a:	006595b3          	sll	a1,a1,t1
1c00853e:	0108d513          	srli	a0,a7,0x10
1c008542:	8dd1                	or	a1,a1,a2
1c008544:	02a77633          	remu	a2,a4,a0
1c008548:	02a75733          	divu	a4,a4,a0
1c00854c:	1008d833          	p.exthz	a6,a7
1c008550:	0642                	slli	a2,a2,0x10
1c008552:	0105d693          	srli	a3,a1,0x10
1c008556:	02e80733          	mul	a4,a6,a4
1c00855a:	8ed1                	or	a3,a3,a2
1c00855c:	00e6f863          	bleu	a4,a3,1c00856c <__umoddi3+0x194>
1c008560:	96c6                	add	a3,a3,a7
1c008562:	0116e563          	bltu	a3,a7,1c00856c <__umoddi3+0x194>
1c008566:	00e6f363          	bleu	a4,a3,1c00856c <__umoddi3+0x194>
1c00856a:	96c6                	add	a3,a3,a7
1c00856c:	8e99                	sub	a3,a3,a4
1c00856e:	02a6f733          	remu	a4,a3,a0
1c008572:	02a6d6b3          	divu	a3,a3,a0
1c008576:	df0725b3          	p.insert	a1,a4,15,16
1c00857a:	02d806b3          	mul	a3,a6,a3
1c00857e:	00d5f863          	bleu	a3,a1,1c00858e <__umoddi3+0x1b6>
1c008582:	95c6                	add	a1,a1,a7
1c008584:	0115e563          	bltu	a1,a7,1c00858e <__umoddi3+0x1b6>
1c008588:	00d5f363          	bleu	a3,a1,1c00858e <__umoddi3+0x1b6>
1c00858c:	95c6                	add	a1,a1,a7
1c00858e:	8d95                	sub	a1,a1,a3
1c008590:	bf25                	j	1c0084c8 <__umoddi3+0xf0>
1c008592:	eed5e9e3          	bltu	a1,a3,1c008484 <__umoddi3+0xac>
1c008596:	6741                	lui	a4,0x10
1c008598:	04e6f563          	bleu	a4,a3,1c0085e2 <__umoddi3+0x20a>
1c00859c:	0ff00e93          	li	t4,255
1c0085a0:	00deb733          	sltu	a4,t4,a3
1c0085a4:	070e                	slli	a4,a4,0x3
1c0085a6:	1c001337          	lui	t1,0x1c001
1c0085aa:	00e6d8b3          	srl	a7,a3,a4
1c0085ae:	86830313          	addi	t1,t1,-1944 # 1c000868 <__DTOR_END__>
1c0085b2:	989a                	add	a7,a7,t1
1c0085b4:	0008ce83          	lbu	t4,0(a7)
1c0085b8:	02000e13          	li	t3,32
1c0085bc:	9eba                	add	t4,t4,a4
1c0085be:	41de0e33          	sub	t3,t3,t4
1c0085c2:	020e1763          	bnez	t3,1c0085f0 <__umoddi3+0x218>
1c0085c6:	00b6e463          	bltu	a3,a1,1c0085ce <__umoddi3+0x1f6>
1c0085ca:	00c56963          	bltu	a0,a2,1c0085dc <__umoddi3+0x204>
1c0085ce:	40c507b3          	sub	a5,a0,a2
1c0085d2:	8d95                	sub	a1,a1,a3
1c0085d4:	00f53533          	sltu	a0,a0,a5
1c0085d8:	40a58833          	sub	a6,a1,a0
1c0085dc:	853e                	mv	a0,a5
1c0085de:	85c2                	mv	a1,a6
1c0085e0:	b555                	j	1c008484 <__umoddi3+0xac>
1c0085e2:	010008b7          	lui	a7,0x1000
1c0085e6:	4741                	li	a4,16
1c0085e8:	fb16efe3          	bltu	a3,a7,1c0085a6 <__umoddi3+0x1ce>
1c0085ec:	4761                	li	a4,24
1c0085ee:	bf65                	j	1c0085a6 <__umoddi3+0x1ce>
1c0085f0:	01d65733          	srl	a4,a2,t4
1c0085f4:	01c696b3          	sll	a3,a3,t3
1c0085f8:	8ed9                	or	a3,a3,a4
1c0085fa:	01d5d7b3          	srl	a5,a1,t4
1c0085fe:	0106d813          	srli	a6,a3,0x10
1c008602:	0307f333          	remu	t1,a5,a6
1c008606:	01d558b3          	srl	a7,a0,t4
1c00860a:	0307d7b3          	divu	a5,a5,a6
1c00860e:	01c595b3          	sll	a1,a1,t3
1c008612:	00b8e5b3          	or	a1,a7,a1
1c008616:	0342                	slli	t1,t1,0x10
1c008618:	1006d733          	p.exthz	a4,a3
1c00861c:	0105d893          	srli	a7,a1,0x10
1c008620:	011368b3          	or	a7,t1,a7
1c008624:	02f70f33          	mul	t5,a4,a5
1c008628:	01c61633          	sll	a2,a2,t3
1c00862c:	01c51533          	sll	a0,a0,t3
1c008630:	833e                	mv	t1,a5
1c008632:	01e8fc63          	bleu	t5,a7,1c00864a <__umoddi3+0x272>
1c008636:	98b6                	add	a7,a7,a3
1c008638:	fff78313          	addi	t1,a5,-1 # ffffff <__l1_heap_size+0xff002f>
1c00863c:	00d8e763          	bltu	a7,a3,1c00864a <__umoddi3+0x272>
1c008640:	01e8f563          	bleu	t5,a7,1c00864a <__umoddi3+0x272>
1c008644:	ffe78313          	addi	t1,a5,-2
1c008648:	98b6                	add	a7,a7,a3
1c00864a:	41e888b3          	sub	a7,a7,t5
1c00864e:	0308f7b3          	remu	a5,a7,a6
1c008652:	0308d8b3          	divu	a7,a7,a6
1c008656:	df07a5b3          	p.insert	a1,a5,15,16
1c00865a:	03170733          	mul	a4,a4,a7
1c00865e:	87c6                	mv	a5,a7
1c008660:	00e5fc63          	bleu	a4,a1,1c008678 <__umoddi3+0x2a0>
1c008664:	95b6                	add	a1,a1,a3
1c008666:	fff88793          	addi	a5,a7,-1 # ffffff <__l1_heap_size+0xff002f>
1c00866a:	00d5e763          	bltu	a1,a3,1c008678 <__umoddi3+0x2a0>
1c00866e:	00e5f563          	bleu	a4,a1,1c008678 <__umoddi3+0x2a0>
1c008672:	ffe88793          	addi	a5,a7,-2
1c008676:	95b6                	add	a1,a1,a3
1c008678:	0342                	slli	t1,t1,0x10
1c00867a:	6f41                	lui	t5,0x10
1c00867c:	00f36333          	or	t1,t1,a5
1c008680:	ffff0793          	addi	a5,t5,-1 # ffff <__l1_heap_size+0x2f>
1c008684:	00f37833          	and	a6,t1,a5
1c008688:	01035313          	srli	t1,t1,0x10
1c00868c:	8ff1                	and	a5,a5,a2
1c00868e:	02f808b3          	mul	a7,a6,a5
1c008692:	02f307b3          	mul	a5,t1,a5
1c008696:	8d99                	sub	a1,a1,a4
1c008698:	8fbe                	mv	t6,a5
1c00869a:	01065713          	srli	a4,a2,0x10
1c00869e:	42e80fb3          	p.mac	t6,a6,a4
1c0086a2:	0108d813          	srli	a6,a7,0x10
1c0086a6:	987e                	add	a6,a6,t6
1c0086a8:	02e30333          	mul	t1,t1,a4
1c0086ac:	00f87363          	bleu	a5,a6,1c0086b2 <__umoddi3+0x2da>
1c0086b0:	937a                	add	t1,t1,t5
1c0086b2:	01085713          	srli	a4,a6,0x10
1c0086b6:	933a                	add	t1,t1,a4
1c0086b8:	6741                	lui	a4,0x10
1c0086ba:	177d                	addi	a4,a4,-1
1c0086bc:	00e87833          	and	a6,a6,a4
1c0086c0:	0842                	slli	a6,a6,0x10
1c0086c2:	00e8f733          	and	a4,a7,a4
1c0086c6:	9742                	add	a4,a4,a6
1c0086c8:	0065e663          	bltu	a1,t1,1c0086d4 <__umoddi3+0x2fc>
1c0086cc:	00659d63          	bne	a1,t1,1c0086e6 <__umoddi3+0x30e>
1c0086d0:	00e57b63          	bleu	a4,a0,1c0086e6 <__umoddi3+0x30e>
1c0086d4:	40c70633          	sub	a2,a4,a2
1c0086d8:	00c73733          	sltu	a4,a4,a2
1c0086dc:	40d30333          	sub	t1,t1,a3
1c0086e0:	40e30333          	sub	t1,t1,a4
1c0086e4:	8732                	mv	a4,a2
1c0086e6:	40e50733          	sub	a4,a0,a4
1c0086ea:	00e53533          	sltu	a0,a0,a4
1c0086ee:	406585b3          	sub	a1,a1,t1
1c0086f2:	8d89                	sub	a1,a1,a0
1c0086f4:	01d597b3          	sll	a5,a1,t4
1c0086f8:	01c75733          	srl	a4,a4,t3
1c0086fc:	00e7e533          	or	a0,a5,a4
1c008700:	01c5d5b3          	srl	a1,a1,t3
1c008704:	b341                	j	1c008484 <__umoddi3+0xac>

1c008706 <__extendsfdf2>:
1c008706:	002027f3          	csrr	a5,0x2
1c00870a:	cf751633          	p.extractu	a2,a0,7,23
1c00870e:	00160713          	addi	a4,a2,1 # 1000001 <__l1_heap_size+0xff0031>
1c008712:	ee873733          	p.bclr	a4,a4,23,8
1c008716:	4685                	li	a3,1
1c008718:	ec0517b3          	p.extractu	a5,a0,22,0
1c00871c:	817d                	srli	a0,a0,0x1f
1c00871e:	00e6d963          	ble	a4,a3,1c008730 <__extendsfdf2+0x2a>
1c008722:	0037d713          	srli	a4,a5,0x3
1c008726:	38060613          	addi	a2,a2,896
1c00872a:	07f6                	slli	a5,a5,0x1d
1c00872c:	4681                	li	a3,0
1c00872e:	a899                	j	1c008784 <__extendsfdf2+0x7e>
1c008730:	ee05                	bnez	a2,1c008768 <__extendsfdf2+0x62>
1c008732:	c7ad                	beqz	a5,1c00879c <__extendsfdf2+0x96>
1c008734:	477d                	li	a4,31
1c008736:	100796b3          	p.fl1	a3,a5
1c00873a:	40d706b3          	sub	a3,a4,a3
1c00873e:	4729                	li	a4,10
1c008740:	00d74e63          	blt	a4,a3,1c00875c <__extendsfdf2+0x56>
1c008744:	472d                	li	a4,11
1c008746:	8f15                	sub	a4,a4,a3
1c008748:	01568613          	addi	a2,a3,21
1c00874c:	00e7d733          	srl	a4,a5,a4
1c008750:	00c797b3          	sll	a5,a5,a2
1c008754:	38900613          	li	a2,905
1c008758:	8e15                	sub	a2,a2,a3
1c00875a:	bfc9                	j	1c00872c <__extendsfdf2+0x26>
1c00875c:	ff568713          	addi	a4,a3,-11
1c008760:	00e79733          	sll	a4,a5,a4
1c008764:	4781                	li	a5,0
1c008766:	b7fd                	j	1c008754 <__extendsfdf2+0x4e>
1c008768:	cf8d                	beqz	a5,1c0087a2 <__extendsfdf2+0x9c>
1c00876a:	004006b7          	lui	a3,0x400
1c00876e:	8efd                	and	a3,a3,a5
1c008770:	0037d713          	srli	a4,a5,0x3
1c008774:	0016b693          	seqz	a3,a3
1c008778:	0692                	slli	a3,a3,0x4
1c00877a:	c1374733          	p.bset	a4,a4,0,19
1c00877e:	07f6                	slli	a5,a5,0x1d
1c008780:	7ff00613          	li	a2,2047
1c008784:	4581                	li	a1,0
1c008786:	e60725b3          	p.insert	a1,a4,19,0
1c00878a:	d54625b3          	p.insert	a1,a2,10,20
1c00878e:	c1f525b3          	p.insert	a1,a0,0,31
1c008792:	853e                	mv	a0,a5
1c008794:	c299                	beqz	a3,1c00879a <__extendsfdf2+0x94>
1c008796:	0016a073          	csrs	0x1,a3
1c00879a:	8082                	ret
1c00879c:	4701                	li	a4,0
1c00879e:	4601                	li	a2,0
1c0087a0:	b771                	j	1c00872c <__extendsfdf2+0x26>
1c0087a2:	4701                	li	a4,0
1c0087a4:	7ff00613          	li	a2,2047
1c0087a8:	b751                	j	1c00872c <__extendsfdf2+0x26>

1c0087aa <cpu_perf_get>:
1c0087aa:	14f52563          	p.beqimm	a0,15,1c0088f4 <cpu_perf_get+0x14a>
1c0087ae:	47bd                	li	a5,15
1c0087b0:	02a7e463          	bltu	a5,a0,1c0087d8 <cpu_perf_get+0x2e>
1c0087b4:	14752363          	p.beqimm	a0,7,1c0088fa <cpu_perf_get+0x150>
1c0087b8:	479d                	li	a5,7
1c0087ba:	04a7e163          	bltu	a5,a0,1c0087fc <cpu_perf_get+0x52>
1c0087be:	0e352763          	p.beqimm	a0,3,1c0088ac <cpu_perf_get+0x102>
1c0087c2:	478d                	li	a5,3
1c0087c4:	06a7ee63          	bltu	a5,a0,1c008840 <cpu_perf_get+0x96>
1c0087c8:	10152a63          	p.beqimm	a0,1,1c0088dc <cpu_perf_get+0x132>
1c0087cc:	4785                	li	a5,1
1c0087ce:	0aa7ea63          	bltu	a5,a0,1c008882 <cpu_perf_get+0xd8>
1c0087d2:	78002573          	csrr	a0,pccr0
1c0087d6:	8082                	ret
1c0087d8:	47dd                	li	a5,23
1c0087da:	10f50463          	beq	a0,a5,1c0088e2 <cpu_perf_get+0x138>
1c0087de:	02a7ec63          	bltu	a5,a0,1c008816 <cpu_perf_get+0x6c>
1c0087e2:	47cd                	li	a5,19
1c0087e4:	0af50863          	beq	a0,a5,1c008894 <cpu_perf_get+0xea>
1c0087e8:	06a7ef63          	bltu	a5,a0,1c008866 <cpu_perf_get+0xbc>
1c0087ec:	47c5                	li	a5,17
1c0087ee:	0ef50163          	beq	a0,a5,1c0088d0 <cpu_perf_get+0x126>
1c0087f2:	0ca7e063          	bltu	a5,a0,1c0088b2 <cpu_perf_get+0x108>
1c0087f6:	79002573          	csrr	a0,pccr16
1c0087fa:	8082                	ret
1c0087fc:	08b52f63          	p.beqimm	a0,11,1c00889a <cpu_perf_get+0xf0>
1c008800:	47ad                	li	a5,11
1c008802:	02a7e763          	bltu	a5,a0,1c008830 <cpu_perf_get+0x86>
1c008806:	0e952463          	p.beqimm	a0,9,1c0088ee <cpu_perf_get+0x144>
1c00880a:	47a5                	li	a5,9
1c00880c:	06a7e863          	bltu	a5,a0,1c00887c <cpu_perf_get+0xd2>
1c008810:	78802573          	csrr	a0,pccr8
1c008814:	8082                	ret
1c008816:	47ed                	li	a5,27
1c008818:	08f50763          	beq	a0,a5,1c0088a6 <cpu_perf_get+0xfc>
1c00881c:	02a7ea63          	bltu	a5,a0,1c008850 <cpu_perf_get+0xa6>
1c008820:	47e5                	li	a5,25
1c008822:	0af50463          	beq	a0,a5,1c0088ca <cpu_perf_get+0x120>
1c008826:	06a7e463          	bltu	a5,a0,1c00888e <cpu_perf_get+0xe4>
1c00882a:	79802573          	csrr	a0,pccr24
1c00882e:	8082                	ret
1c008830:	0ad52c63          	p.beqimm	a0,13,1c0088e8 <cpu_perf_get+0x13e>
1c008834:	47b5                	li	a5,13
1c008836:	04a7e063          	bltu	a5,a0,1c008876 <cpu_perf_get+0xcc>
1c00883a:	78c02573          	csrr	a0,pccr12
1c00883e:	8082                	ret
1c008840:	06552f63          	p.beqimm	a0,5,1c0088be <cpu_perf_get+0x114>
1c008844:	4795                	li	a5,5
1c008846:	04a7e163          	bltu	a5,a0,1c008888 <cpu_perf_get+0xde>
1c00884a:	78402573          	csrr	a0,pccr4
1c00884e:	8082                	ret
1c008850:	47f5                	li	a5,29
1c008852:	06f50963          	beq	a0,a5,1c0088c4 <cpu_perf_get+0x11a>
1c008856:	04f56563          	bltu	a0,a5,1c0088a0 <cpu_perf_get+0xf6>
1c00885a:	47f9                	li	a5,30
1c00885c:	0af51263          	bne	a0,a5,1c008900 <cpu_perf_get+0x156>
1c008860:	79e02573          	csrr	a0,pccr30
1c008864:	8082                	ret
1c008866:	47d5                	li	a5,21
1c008868:	06f50763          	beq	a0,a5,1c0088d6 <cpu_perf_get+0x12c>
1c00886c:	04a7e663          	bltu	a5,a0,1c0088b8 <cpu_perf_get+0x10e>
1c008870:	79402573          	csrr	a0,pccr20
1c008874:	8082                	ret
1c008876:	78e02573          	csrr	a0,pccr14
1c00887a:	8082                	ret
1c00887c:	78a02573          	csrr	a0,pccr10
1c008880:	8082                	ret
1c008882:	78202573          	csrr	a0,pccr2
1c008886:	8082                	ret
1c008888:	78602573          	csrr	a0,pccr6
1c00888c:	8082                	ret
1c00888e:	79a02573          	csrr	a0,pccr26
1c008892:	8082                	ret
1c008894:	79302573          	csrr	a0,pccr19
1c008898:	8082                	ret
1c00889a:	78b02573          	csrr	a0,pccr11
1c00889e:	8082                	ret
1c0088a0:	79c02573          	csrr	a0,pccr28
1c0088a4:	8082                	ret
1c0088a6:	79b02573          	csrr	a0,pccr27
1c0088aa:	8082                	ret
1c0088ac:	78302573          	csrr	a0,pccr3
1c0088b0:	8082                	ret
1c0088b2:	79202573          	csrr	a0,pccr18
1c0088b6:	8082                	ret
1c0088b8:	79602573          	csrr	a0,pccr22
1c0088bc:	8082                	ret
1c0088be:	78502573          	csrr	a0,pccr5
1c0088c2:	8082                	ret
1c0088c4:	79d02573          	csrr	a0,pccr29
1c0088c8:	8082                	ret
1c0088ca:	79902573          	csrr	a0,pccr25
1c0088ce:	8082                	ret
1c0088d0:	79102573          	csrr	a0,pccr17
1c0088d4:	8082                	ret
1c0088d6:	79502573          	csrr	a0,pccr21
1c0088da:	8082                	ret
1c0088dc:	78102573          	csrr	a0,pccr1
1c0088e0:	8082                	ret
1c0088e2:	79702573          	csrr	a0,pccr23
1c0088e6:	8082                	ret
1c0088e8:	78d02573          	csrr	a0,pccr13
1c0088ec:	8082                	ret
1c0088ee:	78902573          	csrr	a0,pccr9
1c0088f2:	8082                	ret
1c0088f4:	78f02573          	csrr	a0,pccr15
1c0088f8:	8082                	ret
1c0088fa:	78702573          	csrr	a0,pccr7
1c0088fe:	8082                	ret
1c008900:	4501                	li	a0,0
1c008902:	8082                	ret

1c008904 <run_test>:
1c008904:	7171                	addi	sp,sp,-176
1c008906:	6785                	lui	a5,0x1
1c008908:	d522                	sw	s0,168(sp)
1c00890a:	80078413          	addi	s0,a5,-2048 # 800 <pos_soc_event_callback+0x3b8>
1c00890e:	d706                	sw	ra,172(sp)
1c008910:	d326                	sw	s1,164(sp)
1c008912:	d14a                	sw	s2,160(sp)
1c008914:	cf4e                	sw	s3,156(sp)
1c008916:	cd52                	sw	s4,152(sp)
1c008918:	cb56                	sw	s5,148(sp)
1c00891a:	c95a                	sw	s6,144(sp)
1c00891c:	c75e                	sw	s7,140(sp)
1c00891e:	c562                	sw	s8,136(sp)
1c008920:	c366                	sw	s9,132(sp)
1c008922:	c16a                	sw	s10,128(sp)
1c008924:	deee                	sw	s11,124(sp)
1c008926:	d6a2                	sw	s0,108(sp)
1c008928:	2375                	jal	1c008ed4 <is_master_core>
1c00892a:	24051763          	bnez	a0,1c008b78 <run_test+0x274>
1c00892e:	100004b7          	lui	s1,0x10000
1c008932:	01c48493          	addi	s1,s1,28 # 1000001c <src_a>
1c008936:	2b71                	jal	1c008ed2 <barrier>
1c008938:	f14027f3          	csrr	a5,mhartid
1c00893c:	102009b7          	lui	s3,0x10200
1c008940:	ca579bb3          	p.extractu	s7,a5,5,5
1c008944:	1c0017b7          	lui	a5,0x1c001
1c008948:	96878793          	addi	a5,a5,-1688 # 1c000968 <__DTOR_END__+0x100>
1c00894c:	4401                	li	s0,0
1c00894e:	4b01                	li	s6,0
1c008950:	4a81                	li	s5,0
1c008952:	4d01                	li	s10,0
1c008954:	4c81                	li	s9,0
1c008956:	4c01                	li	s8,0
1c008958:	d802                	sw	zero,48(sp)
1c00895a:	c282                	sw	zero,68(sp)
1c00895c:	c082                	sw	zero,64(sp)
1c00895e:	de02                	sw	zero,60(sp)
1c008960:	dc02                	sw	zero,56(sp)
1c008962:	da02                	sw	zero,52(sp)
1c008964:	cc82                	sw	zero,88(sp)
1c008966:	ca82                	sw	zero,84(sp)
1c008968:	c882                	sw	zero,80(sp)
1c00896a:	c682                	sw	zero,76(sp)
1c00896c:	c482                	sw	zero,72(sp)
1c00896e:	ce82                	sw	zero,92(sp)
1c008970:	4dfd                	li	s11,31
1c008972:	4905                	li	s2,1
1c008974:	40098993          	addi	s3,s3,1024 # 10200400 <__l1_end+0x2003d0>
1c008978:	4a01                	li	s4,0
1c00897a:	4398                	lw	a4,0(a5)
1c00897c:	cc071073          	csrw	0xcc0,a4
1c008980:	0fbb8f63          	beq	s7,s11,1c008a7e <run_test+0x17a>
1c008984:	0329a023          	sw	s2,32(s3)
1c008988:	79fa1073          	csrw	pccr31,s4
1c00898c:	11bb8163          	beq	s7,s11,1c008a8e <run_test+0x18a>
1c008990:	0129ac23          	sw	s2,24(s3)
1c008994:	470d                	li	a4,3
1c008996:	cc171073          	csrw	0xcc1,a4
1c00899a:	56b6                	lw	a3,108(sp)
1c00899c:	4490                	lw	a2,8(s1)
1c00899e:	40cc                	lw	a1,4(s1)
1c0089a0:	4088                	lw	a0,0(s1)
1c0089a2:	2ce1                	jal	1c008c7a <vector_sub>
1c0089a4:	11bb8363          	beq	s7,s11,1c008aaa <run_test+0x1a6>
1c0089a8:	0009a023          	sw	zero,0(s3)
1c0089ac:	cc1a1073          	csrw	0xcc1,s4
1c0089b0:	0a895b63          	ble	s0,s2,1c008a66 <run_test+0x162>
1c0089b4:	13bb8463          	beq	s7,s11,1c008adc <run_test+0x1d8>
1c0089b8:	0089a703          	lw	a4,8(s3)
1c0089bc:	4376                	lw	t1,92(sp)
1c0089be:	933a                	add	t1,t1,a4
1c0089c0:	ce9a                	sw	t1,92(sp)
1c0089c2:	11bb8a63          	beq	s7,s11,1c008ad6 <run_test+0x1d2>
1c0089c6:	78002573          	csrr	a0,pccr0
1c0089ca:	4326                	lw	t1,72(sp)
1c0089cc:	932a                	add	t1,t1,a0
1c0089ce:	c49a                	sw	t1,72(sp)
1c0089d0:	78102773          	csrr	a4,pccr1
1c0089d4:	4336                	lw	t1,76(sp)
1c0089d6:	933a                	add	t1,t1,a4
1c0089d8:	c69a                	sw	t1,76(sp)
1c0089da:	78202773          	csrr	a4,pccr2
1c0089de:	4346                	lw	t1,80(sp)
1c0089e0:	933a                	add	t1,t1,a4
1c0089e2:	c89a                	sw	t1,80(sp)
1c0089e4:	78302773          	csrr	a4,pccr3
1c0089e8:	4356                	lw	t1,84(sp)
1c0089ea:	933a                	add	t1,t1,a4
1c0089ec:	ca9a                	sw	t1,84(sp)
1c0089ee:	0fbb8163          	beq	s7,s11,1c008ad0 <run_test+0x1cc>
1c0089f2:	78402573          	csrr	a0,pccr4
1c0089f6:	47e6                	lw	a5,88(sp)
1c0089f8:	97aa                	add	a5,a5,a0
1c0089fa:	ccbe                	sw	a5,88(sp)
1c0089fc:	78502773          	csrr	a4,pccr5
1c008a00:	5852                	lw	a6,52(sp)
1c008a02:	983a                	add	a6,a6,a4
1c008a04:	da42                	sw	a6,52(sp)
1c008a06:	0dbb8263          	beq	s7,s11,1c008aca <run_test+0x1c6>
1c008a0a:	78602573          	csrr	a0,pccr6
1c008a0e:	5362                	lw	t1,56(sp)
1c008a10:	932a                	add	t1,t1,a0
1c008a12:	dc1a                	sw	t1,56(sp)
1c008a14:	78702773          	csrr	a4,pccr7
1c008a18:	5372                	lw	t1,60(sp)
1c008a1a:	933a                	add	t1,t1,a4
1c008a1c:	de1a                	sw	t1,60(sp)
1c008a1e:	0bbb8363          	beq	s7,s11,1c008ac4 <run_test+0x1c0>
1c008a22:	78802573          	csrr	a0,pccr8
1c008a26:	4306                	lw	t1,64(sp)
1c008a28:	932a                	add	t1,t1,a0
1c008a2a:	c09a                	sw	t1,64(sp)
1c008a2c:	78902773          	csrr	a4,pccr9
1c008a30:	4316                	lw	t1,68(sp)
1c008a32:	933a                	add	t1,t1,a4
1c008a34:	c29a                	sw	t1,68(sp)
1c008a36:	09bb8463          	beq	s7,s11,1c008abe <run_test+0x1ba>
1c008a3a:	78a02573          	csrr	a0,pccr10
1c008a3e:	5342                	lw	t1,48(sp)
1c008a40:	932a                	add	t1,t1,a0
1c008a42:	d81a                	sw	t1,48(sp)
1c008a44:	78c02773          	csrr	a4,pccr12
1c008a48:	9c3a                	add	s8,s8,a4
1c008a4a:	78d02773          	csrr	a4,pccr13
1c008a4e:	9cba                	add	s9,s9,a4
1c008a50:	78e02773          	csrr	a4,pccr14
1c008a54:	9d3a                	add	s10,s10,a4
1c008a56:	07bb8163          	beq	s7,s11,1c008ab8 <run_test+0x1b4>
1c008a5a:	78f02573          	csrr	a0,pccr15
1c008a5e:	9aaa                	add	s5,s5,a0
1c008a60:	79002773          	csrr	a4,pccr16
1c008a64:	9b3a                	add	s6,s6,a4
1c008a66:	08642063          	p.beqimm	s0,6,1c008ae6 <run_test+0x1e2>
1c008a6a:	1c0017b7          	lui	a5,0x1c001
1c008a6e:	96878793          	addi	a5,a5,-1688 # 1c000968 <__DTOR_END__+0x100>
1c008a72:	0405                	addi	s0,s0,1
1c008a74:	4398                	lw	a4,0(a5)
1c008a76:	cc071073          	csrw	0xcc0,a4
1c008a7a:	f1bb95e3          	bne	s7,s11,1c008984 <run_test+0x80>
1c008a7e:	1a10b837          	lui	a6,0x1a10b
1c008a82:	03282023          	sw	s2,32(a6) # 1a10b020 <__l1_end+0xa10aff0>
1c008a86:	79fa1073          	csrw	pccr31,s4
1c008a8a:	f1bb93e3          	bne	s7,s11,1c008990 <run_test+0x8c>
1c008a8e:	1a10b337          	lui	t1,0x1a10b
1c008a92:	01232c23          	sw	s2,24(t1) # 1a10b018 <__l1_end+0xa10afe8>
1c008a96:	470d                	li	a4,3
1c008a98:	cc171073          	csrw	0xcc1,a4
1c008a9c:	56b6                	lw	a3,108(sp)
1c008a9e:	4490                	lw	a2,8(s1)
1c008aa0:	40cc                	lw	a1,4(s1)
1c008aa2:	4088                	lw	a0,0(s1)
1c008aa4:	2ad9                	jal	1c008c7a <vector_sub>
1c008aa6:	f1bb91e3          	bne	s7,s11,1c0089a8 <run_test+0xa4>
1c008aaa:	1a10b7b7          	lui	a5,0x1a10b
1c008aae:	0007a023          	sw	zero,0(a5) # 1a10b000 <__l1_end+0xa10afd0>
1c008ab2:	cc1a1073          	csrw	0xcc1,s4
1c008ab6:	bded                	j	1c0089b0 <run_test+0xac>
1c008ab8:	453d                	li	a0,15
1c008aba:	39c5                	jal	1c0087aa <cpu_perf_get>
1c008abc:	b74d                	j	1c008a5e <run_test+0x15a>
1c008abe:	4529                	li	a0,10
1c008ac0:	31ed                	jal	1c0087aa <cpu_perf_get>
1c008ac2:	bfb5                	j	1c008a3e <run_test+0x13a>
1c008ac4:	4521                	li	a0,8
1c008ac6:	31d5                	jal	1c0087aa <cpu_perf_get>
1c008ac8:	bfb9                	j	1c008a26 <run_test+0x122>
1c008aca:	4519                	li	a0,6
1c008acc:	39f9                	jal	1c0087aa <cpu_perf_get>
1c008ace:	b781                	j	1c008a0e <run_test+0x10a>
1c008ad0:	4511                	li	a0,4
1c008ad2:	39e1                	jal	1c0087aa <cpu_perf_get>
1c008ad4:	b70d                	j	1c0089f6 <run_test+0xf2>
1c008ad6:	4501                	li	a0,0
1c008ad8:	39c9                	jal	1c0087aa <cpu_perf_get>
1c008ada:	bdc5                	j	1c0089ca <run_test+0xc6>
1c008adc:	1a10b837          	lui	a6,0x1a10b
1c008ae0:	00882703          	lw	a4,8(a6) # 1a10b008 <__l1_end+0xa10afd8>
1c008ae4:	bde1                	j	1c0089bc <run_test+0xb8>
1c008ae6:	5342                	lw	t1,48(sp)
1c008ae8:	58e2                	lw	a7,56(sp)
1c008aea:	c61a                	sw	t1,12(sp)
1c008aec:	4316                	lw	t1,68(sp)
1c008aee:	5852                	lw	a6,52(sp)
1c008af0:	c41a                	sw	t1,8(sp)
1c008af2:	4306                	lw	t1,64(sp)
1c008af4:	47e6                	lw	a5,88(sp)
1c008af6:	c21a                	sw	t1,4(sp)
1c008af8:	5372                	lw	t1,60(sp)
1c008afa:	4756                	lw	a4,84(sp)
1c008afc:	46c6                	lw	a3,80(sp)
1c008afe:	4636                	lw	a2,76(sp)
1c008b00:	45a6                	lw	a1,72(sp)
1c008b02:	4576                	lw	a0,92(sp)
1c008b04:	c01a                	sw	t1,0(sp)
1c008b06:	d05a                	sw	s6,32(sp)
1c008b08:	ce56                	sw	s5,28(sp)
1c008b0a:	cc6a                	sw	s10,24(sp)
1c008b0c:	ca66                	sw	s9,20(sp)
1c008b0e:	c862                	sw	s8,16(sp)
1c008b10:	2afd                	jal	1c008d0e <print_stats>
1c008b12:	26c1                	jal	1c008ed2 <barrier>
1c008b14:	26c1                	jal	1c008ed4 <is_master_core>
1c008b16:	e105                	bnez	a0,1c008b36 <run_test+0x232>
1c008b18:	50ba                	lw	ra,172(sp)
1c008b1a:	542a                	lw	s0,168(sp)
1c008b1c:	549a                	lw	s1,164(sp)
1c008b1e:	590a                	lw	s2,160(sp)
1c008b20:	49fa                	lw	s3,156(sp)
1c008b22:	4a6a                	lw	s4,152(sp)
1c008b24:	4ada                	lw	s5,148(sp)
1c008b26:	4b4a                	lw	s6,144(sp)
1c008b28:	4bba                	lw	s7,140(sp)
1c008b2a:	4c2a                	lw	s8,136(sp)
1c008b2c:	4c9a                	lw	s9,132(sp)
1c008b2e:	4d0a                	lw	s10,128(sp)
1c008b30:	5df6                	lw	s11,124(sp)
1c008b32:	614d                	addi	sp,sp,176
1c008b34:	8082                	ret
1c008b36:	6605                	lui	a2,0x1
1c008b38:	1c0015b7          	lui	a1,0x1c001
1c008b3c:	4488                	lw	a0,8(s1)
1c008b3e:	80060613          	addi	a2,a2,-2048 # 800 <pos_soc_event_callback+0x3b8>
1c008b42:	42058593          	addi	a1,a1,1056 # 1c001420 <expected>
1c008b46:	2645                	jal	1c008ee6 <vector_compare>
1c008b48:	ed3d                	bnez	a0,1c008bc6 <run_test+0x2c2>
1c008b4a:	1c0015b7          	lui	a1,0x1c001
1c008b4e:	97458593          	addi	a1,a1,-1676 # 1c000974 <__DTOR_END__+0x10c>
1c008b52:	542a                	lw	s0,168(sp)
1c008b54:	50ba                	lw	ra,172(sp)
1c008b56:	549a                	lw	s1,164(sp)
1c008b58:	590a                	lw	s2,160(sp)
1c008b5a:	49fa                	lw	s3,156(sp)
1c008b5c:	4a6a                	lw	s4,152(sp)
1c008b5e:	4ada                	lw	s5,148(sp)
1c008b60:	4b4a                	lw	s6,144(sp)
1c008b62:	4bba                	lw	s7,140(sp)
1c008b64:	4c2a                	lw	s8,136(sp)
1c008b66:	4c9a                	lw	s9,132(sp)
1c008b68:	4d0a                	lw	s10,128(sp)
1c008b6a:	5df6                	lw	s11,124(sp)
1c008b6c:	1c001537          	lui	a0,0x1c001
1c008b70:	97c50513          	addi	a0,a0,-1668 # 1c00097c <__DTOR_END__+0x114>
1c008b74:	614d                	addi	sp,sp,176
1c008b76:	a501                	j	1c009176 <printf>
1c008b78:	6509                	lui	a0,0x2
1c008b7a:	100004b7          	lui	s1,0x10000
1c008b7e:	26b1                	jal	1c008eca <my_alloc>
1c008b80:	01c48493          	addi	s1,s1,28 # 1000001c <src_a>
1c008b84:	c088                	sw	a0,0(s1)
1c008b86:	6509                	lui	a0,0x2
1c008b88:	2689                	jal	1c008eca <my_alloc>
1c008b8a:	c0c8                	sw	a0,4(s1)
1c008b8c:	6509                	lui	a0,0x2
1c008b8e:	2e35                	jal	1c008eca <my_alloc>
1c008b90:	1c0036b7          	lui	a3,0x1c003
1c008b94:	1c005737          	lui	a4,0x1c005
1c008b98:	408c                	lw	a1,0(s1)
1c008b9a:	40d0                	lw	a2,4(s1)
1c008b9c:	c488                	sw	a0,8(s1)
1c008b9e:	42068693          	addi	a3,a3,1056 # 1c003420 <vec_a>
1c008ba2:	42070713          	addi	a4,a4,1056 # 1c005420 <vec_b>
1c008ba6:	87a2                	mv	a5,s0
1c008ba8:	00c7c0fb          	lp.setup	x1,a5,1c008bc0 <run_test+0x2bc>
1c008bac:	0046a80b          	p.lw	a6,4(a3!)
1c008bb0:	00000313          	li	t1,0
1c008bb4:	0105a22b          	p.sw	a6,4(a1!)
1c008bb8:	0047280b          	p.lw	a6,4(a4!)
1c008bbc:	0106222b          	p.sw	a6,4(a2!)
1c008bc0:	0065222b          	p.sw	t1,4(a0!) # 2004 <pos_soc_event_callback+0x1bbc>
1c008bc4:	bb8d                	j	1c008936 <run_test+0x32>
1c008bc6:	1c0015b7          	lui	a1,0x1c001
1c008bca:	96c58593          	addi	a1,a1,-1684 # 1c00096c <__DTOR_END__+0x104>
1c008bce:	b751                	j	1c008b52 <run_test+0x24e>

1c008bd0 <cluster_entry>:
1c008bd0:	1141                	addi	sp,sp,-16
1c008bd2:	c422                	sw	s0,8(sp)
1c008bd4:	4785                	li	a5,1
1c008bd6:	00204437          	lui	s0,0x204
1c008bda:	c606                	sw	ra,12(sp)
1c008bdc:	08f42223          	sw	a5,132(s0) # 204084 <__l1_heap_size+0x1f40b4>
1c008be0:	20040793          	addi	a5,s0,512
1c008be4:	4705                	li	a4,1
1c008be6:	00e7a023          	sw	a4,0(a5)
1c008bea:	00e7a623          	sw	a4,12(a5)
1c008bee:	22040793          	addi	a5,s0,544
1c008bf2:	10100713          	li	a4,257
1c008bf6:	00e7a023          	sw	a4,0(a5)
1c008bfa:	00e7a623          	sw	a4,12(a5)
1c008bfe:	1c0097b7          	lui	a5,0x1c009
1c008c02:	90478793          	addi	a5,a5,-1788 # 1c008904 <run_test>
1c008c06:	00204737          	lui	a4,0x204
1c008c0a:	08f72023          	sw	a5,128(a4) # 204080 <__l1_heap_size+0x1f40b0>
1c008c0e:	002047b7          	lui	a5,0x204
1c008c12:	0807a023          	sw	zero,128(a5) # 204080 <__l1_heap_size+0x1f40b0>
1c008c16:	4501                	li	a0,0
1c008c18:	31f5                	jal	1c008904 <run_test>
1c008c1a:	21c40413          	addi	s0,s0,540
1c008c1e:	401c                	lw	a5,0(s0)
1c008c20:	40b2                	lw	ra,12(sp)
1c008c22:	4422                	lw	s0,8(sp)
1c008c24:	0141                	addi	sp,sp,16
1c008c26:	8082                	ret

1c008c28 <main>:
1c008c28:	711d                	addi	sp,sp,-96
1c008c2a:	0808                	addi	a0,sp,16
1c008c2c:	ce86                	sw	ra,92(sp)
1c008c2e:	cca2                	sw	s0,88(sp)
1c008c30:	5d2020ef          	jal	ra,1c00b202 <pi_cluster_conf_init>
1c008c34:	080c                	addi	a1,sp,16
1c008c36:	0048                	addi	a0,sp,4
1c008c38:	190020ef          	jal	ra,1c00adc8 <pi_open_from_conf>
1c008c3c:	0048                	addi	a0,sp,4
1c008c3e:	5ce020ef          	jal	ra,1c00b20c <pi_cluster_open>
1c008c42:	842a                	mv	s0,a0
1c008c44:	c519                	beqz	a0,1c008c52 <main+0x2a>
1c008c46:	1c0077b7          	lui	a5,0x1c007
1c008c4a:	8522                	mv	a0,s0
1c008c4c:	4287a023          	sw	s0,1056(a5) # 1c007420 <_edata>
1c008c50:	29cd                	jal	1c009142 <exit>
1c008c52:	1c0097b7          	lui	a5,0x1c009
1c008c56:	bd078793          	addi	a5,a5,-1072 # 1c008bd0 <cluster_entry>
1c008c5a:	d43e                	sw	a5,40(sp)
1c008c5c:	102c                	addi	a1,sp,40
1c008c5e:	47a1                	li	a5,8
1c008c60:	0048                	addi	a0,sp,4
1c008c62:	d602                	sw	zero,44(sp)
1c008c64:	d802                	sw	zero,48(sp)
1c008c66:	da02                	sw	zero,52(sp)
1c008c68:	de3e                	sw	a5,60(sp)
1c008c6a:	78c020ef          	jal	ra,1c00b3f6 <pi_cluster_send_task_to_cl>
1c008c6e:	842a                	mv	s0,a0
1c008c70:	f979                	bnez	a0,1c008c46 <main+0x1e>
1c008c72:	0048                	addi	a0,sp,4
1c008c74:	700020ef          	jal	ra,1c00b374 <pi_cluster_close>
1c008c78:	b7f9                	j	1c008c46 <main+0x1e>

1c008c7a <vector_sub>:
1c008c7a:	01f6d793          	srli	a5,a3,0x1f
1c008c7e:	1141                	addi	sp,sp,-16
1c008c80:	97b6                	add	a5,a5,a3
1c008c82:	4017d813          	srai	a6,a5,0x1
1c008c86:	c622                	sw	s0,12(sp)
1c008c88:	83fd                	srli	a5,a5,0x1f
1c008c8a:	f1402473          	csrr	s0,mhartid
1c008c8e:	f4543433          	p.bclr	s0,s0,26,5
1c008c92:	00f80733          	add	a4,a6,a5
1c008c96:	02d40433          	mul	s0,s0,a3
1c008c9a:	00140893          	addi	a7,s0,1
1c008c9e:	fc173733          	p.bclr	a4,a4,30,1
1c008ca2:	00241313          	slli	t1,s0,0x2
1c008ca6:	088a                	slli	a7,a7,0x2
1c008ca8:	c426                	sw	s1,8(sp)
1c008caa:	40f704b3          	sub	s1,a4,a5
1c008cae:	4785                	li	a5,1
1c008cb0:	00650fb3          	add	t6,a0,t1
1c008cb4:	00658f33          	add	t5,a1,t1
1c008cb8:	01150eb3          	add	t4,a0,a7
1c008cbc:	01158e33          	add	t3,a1,a7
1c008cc0:	9332                	add	t1,t1,a2
1c008cc2:	98b2                	add	a7,a7,a2
1c008cc4:	04f86833          	p.max	a6,a6,a5
1c008cc8:	010840fb          	lp.setup	x1,a6,1c008ce8 <vector_sub+0x6e>
1c008ccc:	008fa70b          	p.lw	a4,8(t6!)
1c008cd0:	008f238b          	p.lw	t2,8(t5!)
1c008cd4:	008ea78b          	p.lw	a5,8(t4!)
1c008cd8:	008e228b          	p.lw	t0,8(t3!)
1c008cdc:	08777753          	fsub.s	a4,a4,t2
1c008ce0:	0857f7d3          	fsub.s	a5,a5,t0
1c008ce4:	00e3242b          	p.sw	a4,8(t1!)
1c008ce8:	00f8a42b          	p.sw	a5,8(a7!)
1c008cec:	cc81                	beqz	s1,1c008d04 <vector_sub+0x8a>
1c008cee:	96a2                	add	a3,a3,s0
1c008cf0:	068a                	slli	a3,a3,0x2
1c008cf2:	16f1                	addi	a3,a3,-4
1c008cf4:	20d57503          	p.lw	a0,a3(a0)
1c008cf8:	20d5f583          	p.lw	a1,a3(a1)
1c008cfc:	08b575d3          	fsub.s	a1,a0,a1
1c008d00:	00b666a3          	p.sw	a1,a3(a2)
1c008d04:	4432                	lw	s0,12(sp)
1c008d06:	44a2                	lw	s1,8(sp)
1c008d08:	4501                	li	a0,0
1c008d0a:	0141                	addi	sp,sp,16
1c008d0c:	8082                	ret

1c008d0e <print_stats>:
1c008d0e:	711d                	addi	sp,sp,-96
1c008d10:	d86a                	sw	s10,48(sp)
1c008d12:	8d3e                	mv	s10,a5
1c008d14:	57b6                	lw	a5,108(sp)
1c008d16:	cca2                	sw	s0,88(sp)
1c008d18:	c83e                	sw	a5,16(sp)
1c008d1a:	57c6                	lw	a5,112(sp)
1c008d1c:	c8ca                	sw	s2,80(sp)
1c008d1e:	ca3e                	sw	a5,20(sp)
1c008d20:	57e6                	lw	a5,120(sp)
1c008d22:	c6ce                	sw	s3,76(sp)
1c008d24:	cc3e                	sw	a5,24(sp)
1c008d26:	478a                	lw	a5,128(sp)
1c008d28:	c4d2                	sw	s4,72(sp)
1c008d2a:	c2d6                	sw	s5,68(sp)
1c008d2c:	c0da                	sw	s6,64(sp)
1c008d2e:	de5e                	sw	s7,60(sp)
1c008d30:	dc62                	sw	s8,56(sp)
1c008d32:	da66                	sw	s9,52(sp)
1c008d34:	d66e                	sw	s11,44(sp)
1c008d36:	f1402473          	csrr	s0,mhartid
1c008d3a:	ce86                	sw	ra,92(sp)
1c008d3c:	caa6                	sw	s1,84(sp)
1c008d3e:	f4543433          	p.bclr	s0,s0,26,5
1c008d42:	ce3e                	sw	a5,28(sp)
1c008d44:	892a                	mv	s2,a0
1c008d46:	8dae                	mv	s11,a1
1c008d48:	89b2                	mv	s3,a2
1c008d4a:	8cc2                	mv	s9,a6
1c008d4c:	8c46                	mv	s8,a7
1c008d4e:	5b86                	lw	s7,96(sp)
1c008d50:	5b16                	lw	s6,100(sp)
1c008d52:	5aa6                	lw	s5,104(sp)
1c008d54:	5a56                	lw	s4,116(sp)
1c008d56:	e811                	bnez	s0,1c008d6a <print_stats+0x5c>
1c008d58:	1c001537          	lui	a0,0x1c001
1c008d5c:	98c50513          	addi	a0,a0,-1652 # 1c00098c <__DTOR_END__+0x124>
1c008d60:	c636                	sw	a3,12(sp)
1c008d62:	c43a                	sw	a4,8(sp)
1c008d64:	26ad                	jal	1c0090ce <puts>
1c008d66:	4722                	lw	a4,8(sp)
1c008d68:	46b2                	lw	a3,12(sp)
1c008d6a:	4495                	li	s1,5
1c008d6c:	c43a                	sw	a4,8(sp)
1c008d6e:	c636                	sw	a3,12(sp)
1c008d70:	228d                	jal	1c008ed2 <barrier>
1c008d72:	02995633          	divu	a2,s2,s1
1c008d76:	1c001537          	lui	a0,0x1c001
1c008d7a:	85a2                	mv	a1,s0
1c008d7c:	9a850513          	addi	a0,a0,-1624 # 1c0009a8 <__DTOR_END__+0x140>
1c008d80:	2edd                	jal	1c009176 <printf>
1c008d82:	029dd633          	divu	a2,s11,s1
1c008d86:	1c001537          	lui	a0,0x1c001
1c008d8a:	85a2                	mv	a1,s0
1c008d8c:	9bc50513          	addi	a0,a0,-1604 # 1c0009bc <__DTOR_END__+0x154>
1c008d90:	26dd                	jal	1c009176 <printf>
1c008d92:	0299d633          	divu	a2,s3,s1
1c008d96:	1c001537          	lui	a0,0x1c001
1c008d9a:	85a2                	mv	a1,s0
1c008d9c:	9d450513          	addi	a0,a0,-1580 # 1c0009d4 <__DTOR_END__+0x16c>
1c008da0:	2ed9                	jal	1c009176 <printf>
1c008da2:	46b2                	lw	a3,12(sp)
1c008da4:	1c001537          	lui	a0,0x1c001
1c008da8:	0296d633          	divu	a2,a3,s1
1c008dac:	85a2                	mv	a1,s0
1c008dae:	9ec50513          	addi	a0,a0,-1556 # 1c0009ec <__DTOR_END__+0x184>
1c008db2:	26d1                	jal	1c009176 <printf>
1c008db4:	4722                	lw	a4,8(sp)
1c008db6:	1c001537          	lui	a0,0x1c001
1c008dba:	02975633          	divu	a2,a4,s1
1c008dbe:	85a2                	mv	a1,s0
1c008dc0:	a0450513          	addi	a0,a0,-1532 # 1c000a04 <__DTOR_END__+0x19c>
1c008dc4:	2e4d                	jal	1c009176 <printf>
1c008dc6:	029d5633          	divu	a2,s10,s1
1c008dca:	1c001537          	lui	a0,0x1c001
1c008dce:	85a2                	mv	a1,s0
1c008dd0:	a2050513          	addi	a0,a0,-1504 # 1c000a20 <__DTOR_END__+0x1b8>
1c008dd4:	264d                	jal	1c009176 <printf>
1c008dd6:	029cd633          	divu	a2,s9,s1
1c008dda:	1c001537          	lui	a0,0x1c001
1c008dde:	85a2                	mv	a1,s0
1c008de0:	a3850513          	addi	a0,a0,-1480 # 1c000a38 <__DTOR_END__+0x1d0>
1c008de4:	2e49                	jal	1c009176 <printf>
1c008de6:	029c5633          	divu	a2,s8,s1
1c008dea:	1c001537          	lui	a0,0x1c001
1c008dee:	85a2                	mv	a1,s0
1c008df0:	a5050513          	addi	a0,a0,-1456 # 1c000a50 <__DTOR_END__+0x1e8>
1c008df4:	2649                	jal	1c009176 <printf>
1c008df6:	029bd633          	divu	a2,s7,s1
1c008dfa:	1c001537          	lui	a0,0x1c001
1c008dfe:	85a2                	mv	a1,s0
1c008e00:	a6c50513          	addi	a0,a0,-1428 # 1c000a6c <__DTOR_END__+0x204>
1c008e04:	2e8d                	jal	1c009176 <printf>
1c008e06:	029b5633          	divu	a2,s6,s1
1c008e0a:	1c001537          	lui	a0,0x1c001
1c008e0e:	85a2                	mv	a1,s0
1c008e10:	a8050513          	addi	a0,a0,-1408 # 1c000a80 <__DTOR_END__+0x218>
1c008e14:	268d                	jal	1c009176 <printf>
1c008e16:	029ad633          	divu	a2,s5,s1
1c008e1a:	1c001537          	lui	a0,0x1c001
1c008e1e:	85a2                	mv	a1,s0
1c008e20:	a9850513          	addi	a0,a0,-1384 # 1c000a98 <__DTOR_END__+0x230>
1c008e24:	2e89                	jal	1c009176 <printf>
1c008e26:	47c2                	lw	a5,16(sp)
1c008e28:	1c001537          	lui	a0,0x1c001
1c008e2c:	0297d633          	divu	a2,a5,s1
1c008e30:	85a2                	mv	a1,s0
1c008e32:	ab450513          	addi	a0,a0,-1356 # 1c000ab4 <__DTOR_END__+0x24c>
1c008e36:	2681                	jal	1c009176 <printf>
1c008e38:	47d2                	lw	a5,20(sp)
1c008e3a:	1c001537          	lui	a0,0x1c001
1c008e3e:	0297d633          	divu	a2,a5,s1
1c008e42:	85a2                	mv	a1,s0
1c008e44:	ad450513          	addi	a0,a0,-1324 # 1c000ad4 <__DTOR_END__+0x26c>
1c008e48:	263d                	jal	1c009176 <printf>
1c008e4a:	47e2                	lw	a5,24(sp)
1c008e4c:	1c001537          	lui	a0,0x1c001
1c008e50:	0297d633          	divu	a2,a5,s1
1c008e54:	85a2                	mv	a1,s0
1c008e56:	af050513          	addi	a0,a0,-1296 # 1c000af0 <__DTOR_END__+0x288>
1c008e5a:	2e31                	jal	1c009176 <printf>
1c008e5c:	029a5a33          	divu	s4,s4,s1
1c008e60:	1c001537          	lui	a0,0x1c001
1c008e64:	8652                	mv	a2,s4
1c008e66:	85a2                	mv	a1,s0
1c008e68:	b1050513          	addi	a0,a0,-1264 # 1c000b10 <__DTOR_END__+0x2a8>
1c008e6c:	2629                	jal	1c009176 <printf>
1c008e6e:	1c001537          	lui	a0,0x1c001
1c008e72:	8652                	mv	a2,s4
1c008e74:	85a2                	mv	a1,s0
1c008e76:	b3050513          	addi	a0,a0,-1232 # 1c000b30 <__DTOR_END__+0x2c8>
1c008e7a:	2cf5                	jal	1c009176 <printf>
1c008e7c:	47f2                	lw	a5,28(sp)
1c008e7e:	1c001537          	lui	a0,0x1c001
1c008e82:	0297d633          	divu	a2,a5,s1
1c008e86:	85a2                	mv	a1,s0
1c008e88:	b5050513          	addi	a0,a0,-1200 # 1c000b50 <__DTOR_END__+0x2e8>
1c008e8c:	24ed                	jal	1c009176 <printf>
1c008e8e:	d019f553          	fcvt.s.wu	a0,s3
1c008e92:	d0197953          	fcvt.s.wu	s2,s2
1c008e96:	19257553          	fdiv.s	a0,a0,s2
1c008e9a:	86dff0ef          	jal	ra,1c008706 <__extendsfdf2>
1c008e9e:	86ae                	mv	a3,a1
1c008ea0:	85a2                	mv	a1,s0
1c008ea2:	4466                	lw	s0,88(sp)
1c008ea4:	40f6                	lw	ra,92(sp)
1c008ea6:	44d6                	lw	s1,84(sp)
1c008ea8:	4946                	lw	s2,80(sp)
1c008eaa:	49b6                	lw	s3,76(sp)
1c008eac:	4a26                	lw	s4,72(sp)
1c008eae:	4a96                	lw	s5,68(sp)
1c008eb0:	4b06                	lw	s6,64(sp)
1c008eb2:	5bf2                	lw	s7,60(sp)
1c008eb4:	5c62                	lw	s8,56(sp)
1c008eb6:	5cd2                	lw	s9,52(sp)
1c008eb8:	5d42                	lw	s10,48(sp)
1c008eba:	5db2                	lw	s11,44(sp)
1c008ebc:	862a                	mv	a2,a0
1c008ebe:	1c001537          	lui	a0,0x1c001
1c008ec2:	b7050513          	addi	a0,a0,-1168 # 1c000b70 <__DTOR_END__+0x308>
1c008ec6:	6125                	addi	sp,sp,96
1c008ec8:	a47d                	j	1c009176 <printf>

1c008eca <my_alloc>:
1c008eca:	85aa                	mv	a1,a0
1c008ecc:	4501                	li	a0,0
1c008ece:	0ae0206f          	j	1c00af7c <pi_cl_l1_malloc>

1c008ed2 <barrier>:
1c008ed2:	8082                	ret

1c008ed4 <is_master_core>:
1c008ed4:	f1402573          	csrr	a0,mhartid
1c008ed8:	f4553533          	p.bclr	a0,a0,26,5
1c008edc:	00153513          	seqz	a0,a0
1c008ee0:	0ff57513          	andi	a0,a0,255
1c008ee4:	8082                	ret

1c008ee6 <vector_compare>:
1c008ee6:	04c05163          	blez	a2,1c008f28 <vector_compare+0x42>
1c008eea:	4198                	lw	a4,0(a1)
1c008eec:	411c                	lw	a5,0(a0)
1c008eee:	08e7f7d3          	fsub.s	a5,a5,a4
1c008ef2:	1c001737          	lui	a4,0x1c001
1c008ef6:	b8072803          	lw	a6,-1152(a4) # 1c000b80 <__DTOR_END__+0x318>
1c008efa:	20f7a7d3          	fabs.s	a5,a5a5
1c008efe:	a0f817d3          	flt.s	a5,a6,a5
1c008f02:	e78d                	bnez	a5,1c008f2c <vector_compare+0x46>
1c008f04:	0511                	addi	a0,a0,4
1c008f06:	0591                	addi	a1,a1,4
1c008f08:	4701                	li	a4,0
1c008f0a:	a821                	j	1c008f22 <vector_compare+0x3c>
1c008f0c:	0045278b          	p.lw	a5,4(a0!)
1c008f10:	0045a68b          	p.lw	a3,4(a1!)
1c008f14:	08d7f7d3          	fsub.s	a5,a5,a3
1c008f18:	20f7a7d3          	fabs.s	a5,a5a5
1c008f1c:	a0f817d3          	flt.s	a5,a6,a5
1c008f20:	e791                	bnez	a5,1c008f2c <vector_compare+0x46>
1c008f22:	0705                	addi	a4,a4,1
1c008f24:	fee614e3          	bne	a2,a4,1c008f0c <vector_compare+0x26>
1c008f28:	4505                	li	a0,1
1c008f2a:	8082                	ret
1c008f2c:	4501                	li	a0,0
1c008f2e:	8082                	ret

1c008f30 <pos_fll_set_freq>:
1c008f30:	100596b3          	p.fl1	a3,a1
1c008f34:	47f5                	li	a5,29
1c008f36:	4705                	li	a4,1
1c008f38:	82d7b7db          	p.subun	a5,a5,a3,1
1c008f3c:	04f767b3          	p.max	a5,a4,a5
1c008f40:	00400693          	li	a3,4
1c008f44:	fff78613          	addi	a2,a5,-1
1c008f48:	00f595b3          	sll	a1,a1,a5
1c008f4c:	00c71733          	sll	a4,a4,a2
1c008f50:	dc05b833          	p.bclr	a6,a1,14,0
1c008f54:	00a68633          	add	a2,a3,a0
1c008f58:	c0f8275b          	p.addunr	a4,a6,a5
1c008f5c:	00c64603          	lbu	a2,12(a2)
1c008f60:	00251813          	slli	a6,a0,0x2
1c008f64:	00e6e823          	p.sw	a4,a6(a3)
1c008f68:	ce19                	beqz	a2,1c008f86 <pos_fll_set_freq+0x56>
1c008f6a:	0512                	slli	a0,a0,0x4
1c008f6c:	0511                	addi	a0,a0,4
1c008f6e:	1a100637          	lui	a2,0x1a100
1c008f72:	20a67683          	p.lw	a3,a0(a2)
1c008f76:	81bd                	srli	a1,a1,0xf
1c008f78:	de05a6b3          	p.insert	a3,a1,15,0
1c008f7c:	0785                	addi	a5,a5,1
1c008f7e:	c7a7a6b3          	p.insert	a3,a5,3,26
1c008f82:	00d66523          	p.sw	a3,a0(a2)
1c008f86:	853a                	mv	a0,a4
1c008f88:	8082                	ret

1c008f8a <pos_fll_init>:
1c008f8a:	00451593          	slli	a1,a0,0x4
1c008f8e:	832a                	mv	t1,a0
1c008f90:	00458e13          	addi	t3,a1,4
1c008f94:	1a100637          	lui	a2,0x1a100
1c008f98:	21c67703          	p.lw	a4,t3(a2)
1c008f9c:	86ba                	mv	a3,a4
1c008f9e:	04074163          	bltz	a4,1c008fe0 <pos_fll_init+0x56>
1c008fa2:	00858793          	addi	a5,a1,8
1c008fa6:	20f67883          	p.lw	a7,a5(a2)
1c008faa:	4519                	li	a0,6
1c008fac:	caa528b3          	p.insert	a7,a0,5,10
1c008fb0:	05000513          	li	a0,80
1c008fb4:	d70528b3          	p.insert	a7,a0,11,16
1c008fb8:	1a100837          	lui	a6,0x1a100
1c008fbc:	011867a3          	p.sw	a7,a5(a6)
1c008fc0:	05b1                	addi	a1,a1,12
1c008fc2:	20b67603          	p.lw	a2,a1(a2)
1c008fc6:	14c00793          	li	a5,332
1c008fca:	d307a633          	p.insert	a2,a5,9,16
1c008fce:	00c865a3          	p.sw	a2,a1(a6)
1c008fd2:	4785                	li	a5,1
1c008fd4:	c1e7a6b3          	p.insert	a3,a5,0,30
1c008fd8:	c1f7a6b3          	p.insert	a3,a5,0,31
1c008fdc:	00d86e23          	p.sw	a3,t3(a6)
1c008fe0:	00400793          	li	a5,4
1c008fe4:	00231613          	slli	a2,t1,0x2
1c008fe8:	963e                	add	a2,a2,a5
1c008fea:	4208                	lw	a0,0(a2)
1c008fec:	ed19                	bnez	a0,1c00900a <pos_fll_init+0x80>
1c008fee:	10075733          	p.exthz	a4,a4
1c008ff2:	c7a696b3          	p.extractu	a3,a3,3,26
1c008ff6:	073e                	slli	a4,a4,0xf
1c008ff8:	16fd                	addi	a3,a3,-1
1c008ffa:	00d75533          	srl	a0,a4,a3
1c008ffe:	c208                	sw	a0,0(a2)
1c009000:	979a                	add	a5,a5,t1
1c009002:	4705                	li	a4,1
1c009004:	00e78623          	sb	a4,12(a5)
1c009008:	8082                	ret
1c00900a:	46f5                	li	a3,29
1c00900c:	10051733          	p.fl1	a4,a0
1c009010:	4585                	li	a1,1
1c009012:	82e6b75b          	p.subun	a4,a3,a4,1
1c009016:	04e5e733          	p.max	a4,a1,a4
1c00901a:	fff70693          	addi	a3,a4,-1
1c00901e:	00e51833          	sll	a6,a0,a4
1c009022:	00d595b3          	sll	a1,a1,a3
1c009026:	dc0838b3          	p.bclr	a7,a6,14,0
1c00902a:	006786b3          	add	a3,a5,t1
1c00902e:	c0e8a5db          	p.addunr	a1,a7,a4
1c009032:	00c6c683          	lbu	a3,12(a3)
1c009036:	c20c                	sw	a1,0(a2)
1c009038:	d6e1                	beqz	a3,1c009000 <pos_fll_init+0x76>
1c00903a:	1a100637          	lui	a2,0x1a100
1c00903e:	21c67683          	p.lw	a3,t3(a2)
1c009042:	00f85813          	srli	a6,a6,0xf
1c009046:	de0826b3          	p.insert	a3,a6,15,0
1c00904a:	0705                	addi	a4,a4,1
1c00904c:	c7a726b3          	p.insert	a3,a4,3,26
1c009050:	00d66e23          	p.sw	a3,t3(a2)
1c009054:	979a                	add	a5,a5,t1
1c009056:	4705                	li	a4,1
1c009058:	00e78623          	sb	a4,12(a5)
1c00905c:	8082                	ret

1c00905e <pos_fll_constructor>:
1c00905e:	00400793          	li	a5,4
1c009062:	0007a023          	sw	zero,0(a5)
1c009066:	0007a223          	sw	zero,4(a5)
1c00906a:	0007a423          	sw	zero,8(a5)
1c00906e:	00079623          	sh	zero,12(a5)
1c009072:	00078723          	sb	zero,14(a5)
1c009076:	8082                	ret

1c009078 <pos_soc_init>:
1c009078:	1141                	addi	sp,sp,-16
1c00907a:	c606                	sw	ra,12(sp)
1c00907c:	c422                	sw	s0,8(sp)
1c00907e:	37c5                	jal	1c00905e <pos_fll_constructor>
1c009080:	4501                	li	a0,0
1c009082:	3721                	jal	1c008f8a <pos_fll_init>
1c009084:	00a02a23          	sw	a0,20(zero) # 14 <pos_freq_domains>
1c009088:	4505                	li	a0,1
1c00908a:	3701                	jal	1c008f8a <pos_fll_init>
1c00908c:	01400413          	li	s0,20
1c009090:	c408                	sw	a0,8(s0)
1c009092:	4509                	li	a0,2
1c009094:	3ddd                	jal	1c008f8a <pos_fll_init>
1c009096:	c048                	sw	a0,4(s0)
1c009098:	40b2                	lw	ra,12(sp)
1c00909a:	4422                	lw	s0,8(sp)
1c00909c:	0141                	addi	sp,sp,16
1c00909e:	8082                	ret

1c0090a0 <strchr>:
1c0090a0:	00054783          	lbu	a5,0(a0)
1c0090a4:	0ff5f593          	andi	a1,a1,255
1c0090a8:	00b78c63          	beq	a5,a1,1c0090c0 <strchr+0x20>
1c0090ac:	cb99                	beqz	a5,1c0090c2 <strchr+0x22>
1c0090ae:	00150793          	addi	a5,a0,1
1c0090b2:	a011                	j	1c0090b6 <strchr+0x16>
1c0090b4:	c719                	beqz	a4,1c0090c2 <strchr+0x22>
1c0090b6:	853e                	mv	a0,a5
1c0090b8:	0017c70b          	p.lbu	a4,1(a5!)
1c0090bc:	feb71ce3          	bne	a4,a1,1c0090b4 <strchr+0x14>
1c0090c0:	8082                	ret
1c0090c2:	0015b593          	seqz	a1,a1
1c0090c6:	40b005b3          	neg	a1,a1
1c0090ca:	8d6d                	and	a0,a0,a1
1c0090cc:	8082                	ret

1c0090ce <puts>:
1c0090ce:	00054783          	lbu	a5,0(a0)
1c0090d2:	f14026f3          	csrr	a3,mhartid
1c0090d6:	c395                	beqz	a5,1c0090fa <puts+0x2c>
1c0090d8:	ca569733          	p.extractu	a4,a3,5,5
1c0090dc:	f1402673          	csrr	a2,mhartid
1c0090e0:	071e                	slli	a4,a4,0x7
1c0090e2:	060e                	slli	a2,a2,0x3
1c0090e4:	1a10f5b7          	lui	a1,0x1a10f
1c0090e8:	972e                	add	a4,a4,a1
1c0090ea:	ee863633          	p.bclr	a2,a2,23,8
1c0090ee:	0505                	addi	a0,a0,1
1c0090f0:	9732                	add	a4,a4,a2
1c0090f2:	c31c                	sw	a5,0(a4)
1c0090f4:	0015478b          	p.lbu	a5,1(a0!)
1c0090f8:	ffed                	bnez	a5,1c0090f2 <puts+0x24>
1c0090fa:	ca5696b3          	p.extractu	a3,a3,5,5
1c0090fe:	1a10f737          	lui	a4,0x1a10f
1c009102:	f14027f3          	csrr	a5,mhartid
1c009106:	069e                	slli	a3,a3,0x7
1c009108:	078e                	slli	a5,a5,0x3
1c00910a:	96ba                	add	a3,a3,a4
1c00910c:	ee87b7b3          	p.bclr	a5,a5,23,8
1c009110:	4729                	li	a4,10
1c009112:	00e6e7a3          	p.sw	a4,a5(a3)
1c009116:	4501                	li	a0,0
1c009118:	8082                	ret

1c00911a <pos_libc_fputc_locked>:
1c00911a:	f14027f3          	csrr	a5,mhartid
1c00911e:	1a10f6b7          	lui	a3,0x1a10f
1c009122:	ca5797b3          	p.extractu	a5,a5,5,5
1c009126:	f1402773          	csrr	a4,mhartid
1c00912a:	079e                	slli	a5,a5,0x7
1c00912c:	070e                	slli	a4,a4,0x3
1c00912e:	0ff57513          	andi	a0,a0,255
1c009132:	ee873733          	p.bclr	a4,a4,23,8
1c009136:	97b6                	add	a5,a5,a3
1c009138:	00a767a3          	p.sw	a0,a5(a4)
1c00913c:	4501                	li	a0,0
1c00913e:	8082                	ret

1c009140 <pos_libc_prf_locked>:
1c009140:	a095                	j	1c0091a4 <pos_libc_prf>

1c009142 <exit>:
1c009142:	1141                	addi	sp,sp,-16
1c009144:	c422                	sw	s0,8(sp)
1c009146:	c606                	sw	ra,12(sp)
1c009148:	842a                	mv	s0,a0
1c00914a:	43d010ef          	jal	ra,1c00ad86 <pos_init_stop>
1c00914e:	c1f44533          	p.bset	a0,s0,0,31
1c009152:	1a1047b7          	lui	a5,0x1a104
1c009156:	0aa7a023          	sw	a0,160(a5) # 1a1040a0 <__l1_end+0xa104070>
1c00915a:	1a10a7b7          	lui	a5,0x1a10a
1c00915e:	577d                	li	a4,-1
1c009160:	80e7a423          	sw	a4,-2040(a5) # 1a109808 <__l1_end+0xa1097d8>
1c009164:	10500073          	wfi
1c009168:	10500073          	wfi
1c00916c:	bfe5                	j	1c009164 <exit+0x22>

1c00916e <pos_io_start>:
1c00916e:	4501                	li	a0,0
1c009170:	8082                	ret

1c009172 <pos_io_stop>:
1c009172:	4501                	li	a0,0
1c009174:	8082                	ret

1c009176 <printf>:
1c009176:	7139                	addi	sp,sp,-64
1c009178:	02410313          	addi	t1,sp,36
1c00917c:	d432                	sw	a2,40(sp)
1c00917e:	862a                	mv	a2,a0
1c009180:	1c009537          	lui	a0,0x1c009
1c009184:	d22e                	sw	a1,36(sp)
1c009186:	d636                	sw	a3,44(sp)
1c009188:	4589                	li	a1,2
1c00918a:	869a                	mv	a3,t1
1c00918c:	11a50513          	addi	a0,a0,282 # 1c00911a <pos_libc_fputc_locked>
1c009190:	ce06                	sw	ra,28(sp)
1c009192:	d83a                	sw	a4,48(sp)
1c009194:	da3e                	sw	a5,52(sp)
1c009196:	dc42                	sw	a6,56(sp)
1c009198:	de46                	sw	a7,60(sp)
1c00919a:	c61a                	sw	t1,12(sp)
1c00919c:	3755                	jal	1c009140 <pos_libc_prf_locked>
1c00919e:	40f2                	lw	ra,28(sp)
1c0091a0:	6121                	addi	sp,sp,64
1c0091a2:	8082                	ret

1c0091a4 <pos_libc_prf>:
1c0091a4:	7119                	addi	sp,sp,-128
1c0091a6:	dca2                	sw	s0,120(sp)
1c0091a8:	1058                	addi	a4,sp,36
1c0091aa:	4401                	li	s0,0
1c0091ac:	d6ce                	sw	s3,108(sp)
1c0091ae:	d4d2                	sw	s4,104(sp)
1c0091b0:	d2d6                	sw	s5,100(sp)
1c0091b2:	cede                	sw	s7,92(sp)
1c0091b4:	cce2                	sw	s8,88(sp)
1c0091b6:	c8ea                	sw	s10,80(sp)
1c0091b8:	de86                	sw	ra,124(sp)
1c0091ba:	daa6                	sw	s1,116(sp)
1c0091bc:	d8ca                	sw	s2,112(sp)
1c0091be:	d0da                	sw	s6,96(sp)
1c0091c0:	cae6                	sw	s9,84(sp)
1c0091c2:	c6ee                	sw	s11,76(sp)
1c0091c4:	89aa                	mv	s3,a0
1c0091c6:	8bae                	mv	s7,a1
1c0091c8:	8d32                	mv	s10,a2
1c0091ca:	8a36                	mv	s4,a3
1c0091cc:	1c001c37          	lui	s8,0x1c001
1c0091d0:	c03a                	sw	a4,0(sp)
1c0091d2:	8aa2                	mv	s5,s0
1c0091d4:	a039                	j	1c0091e2 <pos_libc_prf+0x3e>
1c0091d6:	85de                	mv	a1,s7
1c0091d8:	9982                	jalr	s3
1c0091da:	15f52063          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c0091de:	0a85                	addi	s5,s5,1
1c0091e0:	8d22                	mv	s10,s0
1c0091e2:	000d4503          	lbu	a0,0(s10)
1c0091e6:	001d0413          	addi	s0,s10,1
1c0091ea:	c979                	beqz	a0,1c0092c0 <pos_libc_prf+0x11c>
1c0091ec:	02500793          	li	a5,37
1c0091f0:	fef513e3          	bne	a0,a5,1c0091d6 <pos_libc_prf+0x32>
1c0091f4:	ca02                	sw	zero,20(sp)
1c0091f6:	c802                	sw	zero,16(sp)
1c0091f8:	c602                	sw	zero,12(sp)
1c0091fa:	c402                	sw	zero,8(sp)
1c0091fc:	c202                	sw	zero,4(sp)
1c0091fe:	02300493          	li	s1,35
1c009202:	02d00b13          	li	s6,45
1c009206:	00044c83          	lbu	s9,0(s0)
1c00920a:	00140913          	addi	s2,s0,1
1c00920e:	85e6                	mv	a1,s9
1c009210:	b84c0513          	addi	a0,s8,-1148 # 1c000b84 <__DTOR_END__+0x31c>
1c009214:	8d4a                	mv	s10,s2
1c009216:	8de6                	mv	s11,s9
1c009218:	3561                	jal	1c0090a0 <strchr>
1c00921a:	c91d                	beqz	a0,1c009250 <pos_libc_prf+0xac>
1c00921c:	109c8963          	beq	s9,s1,1c00932e <pos_libc_prf+0x18a>
1c009220:	0194fe63          	bleu	s9,s1,1c00923c <pos_libc_prf+0x98>
1c009224:	116c8163          	beq	s9,s6,1c009326 <pos_libc_prf+0x182>
1c009228:	03000713          	li	a4,48
1c00922c:	0eec8963          	beq	s9,a4,1c00931e <pos_libc_prf+0x17a>
1c009230:	02b00793          	li	a5,43
1c009234:	0afc8763          	beq	s9,a5,1c0092e2 <pos_libc_prf+0x13e>
1c009238:	844a                	mv	s0,s2
1c00923a:	b7f1                	j	1c009206 <pos_libc_prf+0x62>
1c00923c:	080c8263          	beqz	s9,1c0092c0 <pos_libc_prf+0x11c>
1c009240:	02000793          	li	a5,32
1c009244:	fefc9ae3          	bne	s9,a5,1c009238 <pos_libc_prf+0x94>
1c009248:	4785                	li	a5,1
1c00924a:	c83e                	sw	a5,16(sp)
1c00924c:	844a                	mv	s0,s2
1c00924e:	bf65                	j	1c009206 <pos_libc_prf+0x62>
1c009250:	02a00693          	li	a3,42
1c009254:	2edc8263          	beq	s9,a3,1c009538 <pos_libc_prf+0x394>
1c009258:	fd0c8693          	addi	a3,s9,-48
1c00925c:	45a5                	li	a1,9
1c00925e:	4b01                	li	s6,0
1c009260:	0cd5fd63          	bleu	a3,a1,1c00933a <pos_libc_prf+0x196>
1c009264:	02e00793          	li	a5,46
1c009268:	28fd8663          	beq	s11,a5,1c0094f4 <pos_libc_prf+0x350>
1c00926c:	846e                	mv	s0,s11
1c00926e:	54fd                	li	s1,-1
1c009270:	1c001737          	lui	a4,0x1c001
1c009274:	85ee                	mv	a1,s11
1c009276:	b8c70513          	addi	a0,a4,-1140 # 1c000b8c <__DTOR_END__+0x324>
1c00927a:	351d                	jal	1c0090a0 <strchr>
1c00927c:	4781                	li	a5,0
1c00927e:	cd19                	beqz	a0,1c00929c <pos_libc_prf+0xf8>
1c009280:	06c00793          	li	a5,108
1c009284:	001d0693          	addi	a3,s10,1
1c009288:	000d4d83          	lbu	s11,0(s10)
1c00928c:	3af40563          	beq	s0,a5,1c009636 <pos_libc_prf+0x492>
1c009290:	06800793          	li	a5,104
1c009294:	3af40563          	beq	s0,a5,1c00963e <pos_libc_prf+0x49a>
1c009298:	8d36                	mv	s10,a3
1c00929a:	87a2                	mv	a5,s0
1c00929c:	06700693          	li	a3,103
1c0092a0:	0bb6ee63          	bltu	a3,s11,1c00935c <pos_libc_prf+0x1b8>
1c0092a4:	06500693          	li	a3,101
1c0092a8:	3addf2e3          	bleu	a3,s11,1c009e4c <pos_libc_prf+0xca8>
1c0092ac:	04700693          	li	a3,71
1c0092b0:	39b6ed63          	bltu	a3,s11,1c00964a <pos_libc_prf+0x4a6>
1c0092b4:	04500793          	li	a5,69
1c0092b8:	38fdfae3          	bleu	a5,s11,1c009e4c <pos_libc_prf+0xca8>
1c0092bc:	2e0d9863          	bnez	s11,1c0095ac <pos_libc_prf+0x408>
1c0092c0:	8456                	mv	s0,s5
1c0092c2:	8522                	mv	a0,s0
1c0092c4:	50f6                	lw	ra,124(sp)
1c0092c6:	5466                	lw	s0,120(sp)
1c0092c8:	54d6                	lw	s1,116(sp)
1c0092ca:	5946                	lw	s2,112(sp)
1c0092cc:	59b6                	lw	s3,108(sp)
1c0092ce:	5a26                	lw	s4,104(sp)
1c0092d0:	5a96                	lw	s5,100(sp)
1c0092d2:	5b06                	lw	s6,96(sp)
1c0092d4:	4bf6                	lw	s7,92(sp)
1c0092d6:	4c66                	lw	s8,88(sp)
1c0092d8:	4cd6                	lw	s9,84(sp)
1c0092da:	4d46                	lw	s10,80(sp)
1c0092dc:	4db6                	lw	s11,76(sp)
1c0092de:	6109                	addi	sp,sp,128
1c0092e0:	8082                	ret
1c0092e2:	4705                	li	a4,1
1c0092e4:	c63a                	sw	a4,12(sp)
1c0092e6:	844a                	mv	s0,s2
1c0092e8:	bf39                	j	1c009206 <pos_libc_prf+0x62>
1c0092ea:	00044503          	lbu	a0,0(s0)
1c0092ee:	47a5                	li	a5,9
1c0092f0:	fd050693          	addi	a3,a0,-48
1c0092f4:	72d7e9e3          	bltu	a5,a3,1c00a226 <pos_libc_prf+0x1082>
1c0092f8:	00140793          	addi	a5,s0,1
1c0092fc:	8dbe                	mv	s11,a5
1c0092fe:	a809                	j	1c009310 <pos_libc_prf+0x16c>
1c009300:	001dc50b          	p.lbu	a0,1(s11!)
1c009304:	4725                	li	a4,9
1c009306:	fd050793          	addi	a5,a0,-48
1c00930a:	197d                	addi	s2,s2,-1
1c00930c:	70f76ee3          	bltu	a4,a5,1c00a228 <pos_libc_prf+0x1084>
1c009310:	85de                	mv	a1,s7
1c009312:	846e                	mv	s0,s11
1c009314:	9982                	jalr	s3
1c009316:	fff535e3          	p.bneimm	a0,-1,1c009300 <pos_libc_prf+0x15c>
1c00931a:	547d                	li	s0,-1
1c00931c:	b75d                	j	1c0092c2 <pos_libc_prf+0x11e>
1c00931e:	4785                	li	a5,1
1c009320:	ca3e                	sw	a5,20(sp)
1c009322:	844a                	mv	s0,s2
1c009324:	b5cd                	j	1c009206 <pos_libc_prf+0x62>
1c009326:	4705                	li	a4,1
1c009328:	c43a                	sw	a4,8(sp)
1c00932a:	844a                	mv	s0,s2
1c00932c:	bde9                	j	1c009206 <pos_libc_prf+0x62>
1c00932e:	4705                	li	a4,1
1c009330:	c23a                	sw	a4,4(sp)
1c009332:	844a                	mv	s0,s2
1c009334:	bdc9                	j	1c009206 <pos_libc_prf+0x62>
1c009336:	844a                	mv	s0,s2
1c009338:	0905                	addi	s2,s2,1
1c00933a:	002b1793          	slli	a5,s6,0x2
1c00933e:	00094d83          	lbu	s11,0(s2)
1c009342:	97da                	add	a5,a5,s6
1c009344:	0786                	slli	a5,a5,0x1
1c009346:	97e6                	add	a5,a5,s9
1c009348:	fd0d8713          	addi	a4,s11,-48
1c00934c:	fd078b13          	addi	s6,a5,-48
1c009350:	8cee                	mv	s9,s11
1c009352:	fee5f2e3          	bleu	a4,a1,1c009336 <pos_libc_prf+0x192>
1c009356:	00240d13          	addi	s10,s0,2
1c00935a:	b729                	j	1c009264 <pos_libc_prf+0xc0>
1c00935c:	07000693          	li	a3,112
1c009360:	24dd85e3          	beq	s11,a3,1c009daa <pos_libc_prf+0xc06>
1c009364:	1fb6e463          	bltu	a3,s11,1c00954c <pos_libc_prf+0x3a8>
1c009368:	06e00693          	li	a3,110
1c00936c:	20dd8ae3          	beq	s11,a3,1c009d80 <pos_libc_prf+0xbdc>
1c009370:	2fb6e763          	bltu	a3,s11,1c00965e <pos_libc_prf+0x4ba>
1c009374:	06900693          	li	a3,105
1c009378:	2add9ce3          	bne	s11,a3,1c009e30 <pos_libc_prf+0xc8c>
1c00937c:	06c00693          	li	a3,108
1c009380:	00d78a63          	beq	a5,a3,1c009394 <pos_libc_prf+0x1f0>
1c009384:	07a00693          	li	a3,122
1c009388:	00d78663          	beq	a5,a3,1c009394 <pos_libc_prf+0x1f0>
1c00938c:	04c00693          	li	a3,76
1c009390:	5ed78de3          	beq	a5,a3,1c00a18a <pos_libc_prf+0xfe6>
1c009394:	000a2783          	lw	a5,0(s4)
1c009398:	0a11                	addi	s4,s4,4
1c00939a:	41f7d713          	srai	a4,a5,0x1f
1c00939e:	ce52                	sw	s4,28(sp)
1c0093a0:	c23a                	sw	a4,4(sp)
1c0093a2:	4e0741e3          	bltz	a4,1c00a084 <pos_libc_prf+0xee0>
1c0093a6:	4732                	lw	a4,12(sp)
1c0093a8:	440709e3          	beqz	a4,1c009ffa <pos_libc_prf+0xe56>
1c0093ac:	02b00693          	li	a3,43
1c0093b0:	4c92                	lw	s9,4(sp)
1c0093b2:	02d10223          	sb	a3,36(sp)
1c0093b6:	02510a13          	addi	s4,sp,37
1c0093ba:	843e                	mv	s0,a5
1c0093bc:	8dd2                	mv	s11,s4
1c0093be:	a011                	j	1c0093c2 <pos_libc_prf+0x21e>
1c0093c0:	8dca                	mv	s11,s2
1c0093c2:	4629                	li	a2,10
1c0093c4:	4681                	li	a3,0
1c0093c6:	8522                	mv	a0,s0
1c0093c8:	85e6                	mv	a1,s9
1c0093ca:	80eff0ef          	jal	ra,1c0083d8 <__umoddi3>
1c0093ce:	892a                	mv	s2,a0
1c0093d0:	85e6                	mv	a1,s9
1c0093d2:	8522                	mv	a0,s0
1c0093d4:	4629                	li	a2,10
1c0093d6:	4681                	li	a3,0
1c0093d8:	cc5fe0ef          	jal	ra,1c00809c <__udivdi3>
1c0093dc:	03090913          	addi	s2,s2,48
1c0093e0:	012d8023          	sb	s2,0(s11)
1c0093e4:	00a5e7b3          	or	a5,a1,a0
1c0093e8:	001d8913          	addi	s2,s11,1
1c0093ec:	842a                	mv	s0,a0
1c0093ee:	8cae                	mv	s9,a1
1c0093f0:	fbe1                	bnez	a5,1c0093c0 <pos_libc_prf+0x21c>
1c0093f2:	00090023          	sb	zero,0(s2)
1c0093f6:	01ba7d63          	bleu	s11,s4,1c009410 <pos_libc_prf+0x26c>
1c0093fa:	87ee                	mv	a5,s11
1c0093fc:	000a4683          	lbu	a3,0(s4)
1c009400:	0007c703          	lbu	a4,0(a5)
1c009404:	fed78fab          	p.sb	a3,-1(a5!)
1c009408:	00ea00ab          	p.sb	a4,1(s4!)
1c00940c:	fefa68e3          	bltu	s4,a5,1c0093fc <pos_libc_prf+0x258>
1c009410:	4782                	lw	a5,0(sp)
1c009412:	4732                	lw	a4,12(sp)
1c009414:	40f90933          	sub	s2,s2,a5
1c009418:	3c071de3          	bnez	a4,1c009ff2 <pos_libc_prf+0xe4e>
1c00941c:	47c2                	lw	a5,16(sp)
1c00941e:	3c079ae3          	bnez	a5,1c009ff2 <pos_libc_prf+0xe4e>
1c009422:	4712                	lw	a4,4(sp)
1c009424:	837d                	srli	a4,a4,0x1f
1c009426:	c23a                	sw	a4,4(sp)
1c009428:	3404c463          	bltz	s1,1c009770 <pos_libc_prf+0x5cc>
1c00942c:	4712                	lw	a4,4(sp)
1c00942e:	412484b3          	sub	s1,s1,s2
1c009432:	94ba                	add	s1,s1,a4
1c009434:	0404e4b3          	p.max	s1,s1,zero
1c009438:	009907b3          	add	a5,s2,s1
1c00943c:	40fb0b33          	sub	s6,s6,a5
1c009440:	1040                	addi	s0,sp,36
1c009442:	4c81                	li	s9,0
1c009444:	cc02                	sw	zero,24(sp)
1c009446:	4a01                	li	s4,0
1c009448:	4722                	lw	a4,8(sp)
1c00944a:	e305                	bnez	a4,1c00946a <pos_libc_prf+0x2c6>
1c00944c:	01605f63          	blez	s6,1c00946a <pos_libc_prf+0x2c6>
1c009450:	fffb0d93          	addi	s11,s6,-1
1c009454:	85de                	mv	a1,s7
1c009456:	02000513          	li	a0,32
1c00945a:	9982                	jalr	s3
1c00945c:	1dfd                	addi	s11,s11,-1
1c00945e:	ebf52ee3          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c009462:	fffdb9e3          	p.bneimm	s11,-1,1c009454 <pos_libc_prf+0x2b0>
1c009466:	9ada                	add	s5,s5,s6
1c009468:	5b7d                	li	s6,-1
1c00946a:	4792                	lw	a5,4(sp)
1c00946c:	00f40db3          	add	s11,s0,a5
1c009470:	a031                	j	1c00947c <pos_libc_prf+0x2d8>
1c009472:	0014450b          	p.lbu	a0,1(s0!)
1c009476:	9982                	jalr	s3
1c009478:	ebf521e3          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c00947c:	85de                	mv	a1,s7
1c00947e:	ffb41ae3          	bne	s0,s11,1c009472 <pos_libc_prf+0x2ce>
1c009482:	8da6                	mv	s11,s1
1c009484:	a021                	j	1c00948c <pos_libc_prf+0x2e8>
1c009486:	9982                	jalr	s3
1c009488:	e9f529e3          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c00948c:	1dfd                	addi	s11,s11,-1
1c00948e:	85de                	mv	a1,s7
1c009490:	03000513          	li	a0,48
1c009494:	fffdb9e3          	p.bneimm	s11,-1,1c009486 <pos_libc_prf+0x2e2>
1c009498:	4712                	lw	a4,4(sp)
1c00949a:	40e90933          	sub	s2,s2,a4
1c00949e:	c44a                	sw	s2,8(sp)
1c0094a0:	e40a15e3          	bnez	s4,1c0092ea <pos_libc_prf+0x146>
1c0094a4:	47e2                	lw	a5,24(sp)
1c0094a6:	16079763          	bnez	a5,1c009614 <pos_libc_prf+0x470>
1c0094aa:	120c8863          	beqz	s9,1c0095da <pos_libc_prf+0x436>
1c0094ae:	00044783          	lbu	a5,0(s0)
1c0094b2:	4a25                	li	s4,9
1c0094b4:	02e00d93          	li	s11,46
1c0094b8:	a801                	j	1c0094c8 <pos_libc_prf+0x324>
1c0094ba:	0405                	addi	s0,s0,1
1c0094bc:	9982                	jalr	s3
1c0094be:	e5f52ee3          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c0094c2:	00044783          	lbu	a5,0(s0)
1c0094c6:	197d                	addi	s2,s2,-1
1c0094c8:	fd078713          	addi	a4,a5,-48
1c0094cc:	853e                	mv	a0,a5
1c0094ce:	85de                	mv	a1,s7
1c0094d0:	feea75e3          	bleu	a4,s4,1c0094ba <pos_libc_prf+0x316>
1c0094d4:	ffb783e3          	beq	a5,s11,1c0094ba <pos_libc_prf+0x316>
1c0094d8:	8a66                	mv	s4,s9
1c0094da:	85de                	mv	a1,s7
1c0094dc:	03000513          	li	a0,48
1c0094e0:	01404463          	bgtz	s4,1c0094e8 <pos_libc_prf+0x344>
1c0094e4:	0010106f          	j	1c00ace4 <pos_libc_prf+0x1b40>
1c0094e8:	9982                	jalr	s3
1c0094ea:	1a7d                	addi	s4,s4,-1
1c0094ec:	fff537e3          	p.bneimm	a0,-1,1c0094da <pos_libc_prf+0x336>
1c0094f0:	547d                	li	s0,-1
1c0094f2:	bbc1                	j	1c0092c2 <pos_libc_prf+0x11e>
1c0094f4:	000d4d83          	lbu	s11,0(s10)
1c0094f8:	02a00793          	li	a5,42
1c0094fc:	001d0513          	addi	a0,s10,1
1c009500:	08fd8e63          	beq	s11,a5,1c00959c <pos_libc_prf+0x3f8>
1c009504:	fd0d8793          	addi	a5,s11,-48
1c009508:	4825                	li	a6,9
1c00950a:	846e                	mv	s0,s11
1c00950c:	86aa                	mv	a3,a0
1c00950e:	4481                	li	s1,0
1c009510:	45a5                	li	a1,9
1c009512:	8d2a                	mv	s10,a0
1c009514:	d4f86ee3          	bltu	a6,a5,1c009270 <pos_libc_prf+0xcc>
1c009518:	00249793          	slli	a5,s1,0x2
1c00951c:	97a6                	add	a5,a5,s1
1c00951e:	0786                	slli	a5,a5,0x1
1c009520:	97ee                	add	a5,a5,s11
1c009522:	0016cd8b          	p.lbu	s11,1(a3!) # 1a10f001 <__l1_end+0xa10efd1>
1c009526:	fd078493          	addi	s1,a5,-48
1c00952a:	fd0d8793          	addi	a5,s11,-48
1c00952e:	846e                	mv	s0,s11
1c009530:	fef5f4e3          	bleu	a5,a1,1c009518 <pos_libc_prf+0x374>
1c009534:	8d36                	mv	s10,a3
1c009536:	bb2d                	j	1c009270 <pos_libc_prf+0xcc>
1c009538:	000a2b03          	lw	s6,0(s4)
1c00953c:	0a11                	addi	s4,s4,4
1c00953e:	080b4363          	bltz	s6,1c0095c4 <pos_libc_prf+0x420>
1c009542:	00094d83          	lbu	s11,0(s2)
1c009546:	00240d13          	addi	s10,s0,2
1c00954a:	bb29                	j	1c009264 <pos_libc_prf+0xc0>
1c00954c:	07500693          	li	a3,117
1c009550:	10dd8763          	beq	s11,a3,1c00965e <pos_libc_prf+0x4ba>
1c009554:	07800693          	li	a3,120
1c009558:	10dd8363          	beq	s11,a3,1c00965e <pos_libc_prf+0x4ba>
1c00955c:	07300793          	li	a5,115
1c009560:	0cfd98e3          	bne	s11,a5,1c009e30 <pos_libc_prf+0xc8c>
1c009564:	004a0713          	addi	a4,s4,4
1c009568:	ce3a                	sw	a4,28(sp)
1c00956a:	000a2403          	lw	s0,0(s4)
1c00956e:	3c04c2e3          	bltz	s1,1c00a132 <pos_libc_prf+0xf8e>
1c009572:	460481e3          	beqz	s1,1c00a1d4 <pos_libc_prf+0x1030>
1c009576:	00044783          	lbu	a5,0(s0)
1c00957a:	44078ce3          	beqz	a5,1c00a1d2 <pos_libc_prf+0x102e>
1c00957e:	00140793          	addi	a5,s0,1
1c009582:	4901                	li	s2,0
1c009584:	a021                	j	1c00958c <pos_libc_prf+0x3e8>
1c009586:	0017c70b          	p.lbu	a4,1(a5!)
1c00958a:	c701                	beqz	a4,1c009592 <pos_libc_prf+0x3ee>
1c00958c:	0905                	addi	s2,s2,1
1c00958e:	fe994ce3          	blt	s2,s1,1c009586 <pos_libc_prf+0x3e2>
1c009592:	412b0b33          	sub	s6,s6,s2
1c009596:	4481                	li	s1,0
1c009598:	c202                	sw	zero,4(sp)
1c00959a:	b565                	j	1c009442 <pos_libc_prf+0x29e>
1c00959c:	001d4d83          	lbu	s11,1(s10)
1c0095a0:	000a2483          	lw	s1,0(s4)
1c0095a4:	846e                	mv	s0,s11
1c0095a6:	0d09                	addi	s10,s10,2
1c0095a8:	0a11                	addi	s4,s4,4
1c0095aa:	b1d9                	j	1c009270 <pos_libc_prf+0xcc>
1c0095ac:	02500793          	li	a5,37
1c0095b0:	08fd90e3          	bne	s11,a5,1c009e30 <pos_libc_prf+0xc8c>
1c0095b4:	85de                	mv	a1,s7
1c0095b6:	02500513          	li	a0,37
1c0095ba:	9982                	jalr	s3
1c0095bc:	d5f52fe3          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c0095c0:	0a85                	addi	s5,s5,1
1c0095c2:	b105                	j	1c0091e2 <pos_libc_prf+0x3e>
1c0095c4:	4785                	li	a5,1
1c0095c6:	41600b33          	neg	s6,s6
1c0095ca:	c43e                	sw	a5,8(sp)
1c0095cc:	bf9d                	j	1c009542 <pos_libc_prf+0x39e>
1c0095ce:	0014450b          	p.lbu	a0,1(s0!)
1c0095d2:	197d                	addi	s2,s2,-1
1c0095d4:	9982                	jalr	s3
1c0095d6:	d5f522e3          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c0095da:	85de                	mv	a1,s7
1c0095dc:	ff2049e3          	bgtz	s2,1c0095ce <pos_libc_prf+0x42a>
1c0095e0:	4792                	lw	a5,4(sp)
1c0095e2:	4a72                	lw	s4,28(sp)
1c0095e4:	00fa8733          	add	a4,s5,a5
1c0095e8:	47a2                	lw	a5,8(sp)
1c0095ea:	9726                	add	a4,a4,s1
1c0095ec:	00e78ab3          	add	s5,a5,a4
1c0095f0:	bf6059e3          	blez	s6,1c0091e2 <pos_libc_prf+0x3e>
1c0095f4:	9ada                	add	s5,s5,s6
1c0095f6:	1b7d                	addi	s6,s6,-1
1c0095f8:	a029                	j	1c009602 <pos_libc_prf+0x45e>
1c0095fa:	01fb3463          	p.bneimm	s6,-1,1c009602 <pos_libc_prf+0x45e>
1c0095fe:	5fe0106f          	j	1c00abfc <pos_libc_prf+0x1a58>
1c009602:	85de                	mv	a1,s7
1c009604:	02000513          	li	a0,32
1c009608:	9982                	jalr	s3
1c00960a:	1b7d                	addi	s6,s6,-1
1c00960c:	fff537e3          	p.bneimm	a0,-1,1c0095fa <pos_libc_prf+0x456>
1c009610:	547d                	li	s0,-1
1c009612:	b945                	j	1c0092c2 <pos_libc_prf+0x11e>
1c009614:	02e00a13          	li	s4,46
1c009618:	a031                	j	1c009624 <pos_libc_prf+0x480>
1c00961a:	197d                	addi	s2,s2,-1
1c00961c:	014d9463          	bne	s11,s4,1c009624 <pos_libc_prf+0x480>
1c009620:	5320106f          	j	1c00ab52 <pos_libc_prf+0x19ae>
1c009624:	00144d8b          	p.lbu	s11,1(s0!)
1c009628:	85de                	mv	a1,s7
1c00962a:	856e                	mv	a0,s11
1c00962c:	9982                	jalr	s3
1c00962e:	fff536e3          	p.bneimm	a0,-1,1c00961a <pos_libc_prf+0x476>
1c009632:	547d                	li	s0,-1
1c009634:	b179                	j	1c0092c2 <pos_libc_prf+0x11e>
1c009636:	188d83e3          	beq	s11,s0,1c009fbc <pos_libc_prf+0xe18>
1c00963a:	8d36                	mv	s10,a3
1c00963c:	b185                	j	1c00929c <pos_libc_prf+0xf8>
1c00963e:	188d86e3          	beq	s11,s0,1c009fca <pos_libc_prf+0xe26>
1c009642:	8d36                	mv	s10,a3
1c009644:	06800793          	li	a5,104
1c009648:	b991                	j	1c00929c <pos_libc_prf+0xf8>
1c00964a:	06300693          	li	a3,99
1c00964e:	70dd8c63          	beq	s11,a3,1c009d66 <pos_libc_prf+0xbc2>
1c009652:	d3b6e5e3          	bltu	a3,s11,1c00937c <pos_libc_prf+0x1d8>
1c009656:	05800693          	li	a3,88
1c00965a:	7cdd9b63          	bne	s11,a3,1c009e30 <pos_libc_prf+0xc8c>
1c00965e:	06c00693          	li	a3,108
1c009662:	18d780e3          	beq	a5,a3,1c009fe2 <pos_libc_prf+0xe3e>
1c009666:	07a00693          	li	a3,122
1c00966a:	16d78ce3          	beq	a5,a3,1c009fe2 <pos_libc_prf+0xe3e>
1c00966e:	04c00693          	li	a3,76
1c009672:	2cd78ee3          	beq	a5,a3,1c00a14e <pos_libc_prf+0xfaa>
1c009676:	000a2403          	lw	s0,0(s4)
1c00967a:	0a11                	addi	s4,s4,4
1c00967c:	ce52                	sw	s4,28(sp)
1c00967e:	4c81                	li	s9,0
1c009680:	06f00793          	li	a5,111
1c009684:	3cfd81e3          	beq	s11,a5,1c00a246 <pos_libc_prf+0x10a2>
1c009688:	07500793          	li	a5,117
1c00968c:	02410a13          	addi	s4,sp,36
1c009690:	04fd8763          	beq	s11,a5,1c0096de <pos_libc_prf+0x53a>
1c009694:	4712                	lw	a4,4(sp)
1c009696:	2a0708e3          	beqz	a4,1c00a146 <pos_libc_prf+0xfa2>
1c00969a:	77e1                	lui	a5,0xffff8
1c00969c:	8307c793          	xori	a5,a5,-2000
1c0096a0:	02f11223          	sh	a5,36(sp)
1c0096a4:	4909                	li	s2,2
1c0096a6:	02610693          	addi	a3,sp,38
1c0096aa:	87b6                	mv	a5,a3
1c0096ac:	4e25                	li	t3,9
1c0096ae:	f6443733          	p.bclr	a4,s0,27,4
1c0096b2:	01cc9613          	slli	a2,s9,0x1c
1c0096b6:	8011                	srli	s0,s0,0x4
1c0096b8:	8c51                	or	s0,s0,a2
1c0096ba:	004cdc93          	srli	s9,s9,0x4
1c0096be:	05770813          	addi	a6,a4,87
1c0096c2:	03070593          	addi	a1,a4,48
1c0096c6:	01946533          	or	a0,s0,s9
1c0096ca:	06ee7663          	bleu	a4,t3,1c009736 <pos_libc_prf+0x592>
1c0096ce:	01078023          	sb	a6,0(a5) # ffff8000 <pulp__FC+0xffff8001>
1c0096d2:	00178593          	addi	a1,a5,1
1c0096d6:	c52d                	beqz	a0,1c009740 <pos_libc_prf+0x59c>
1c0096d8:	87ae                	mv	a5,a1
1c0096da:	bfd1                	j	1c0096ae <pos_libc_prf+0x50a>
1c0096dc:	8a4a                	mv	s4,s2
1c0096de:	4629                	li	a2,10
1c0096e0:	4681                	li	a3,0
1c0096e2:	8522                	mv	a0,s0
1c0096e4:	85e6                	mv	a1,s9
1c0096e6:	cf3fe0ef          	jal	ra,1c0083d8 <__umoddi3>
1c0096ea:	892a                	mv	s2,a0
1c0096ec:	85e6                	mv	a1,s9
1c0096ee:	8522                	mv	a0,s0
1c0096f0:	4629                	li	a2,10
1c0096f2:	4681                	li	a3,0
1c0096f4:	9a9fe0ef          	jal	ra,1c00809c <__udivdi3>
1c0096f8:	03090913          	addi	s2,s2,48
1c0096fc:	012a0023          	sb	s2,0(s4)
1c009700:	00a5e7b3          	or	a5,a1,a0
1c009704:	001a0913          	addi	s2,s4,1
1c009708:	842a                	mv	s0,a0
1c00970a:	8cae                	mv	s9,a1
1c00970c:	fbe1                	bnez	a5,1c0096dc <pos_libc_prf+0x538>
1c00970e:	4782                	lw	a5,0(sp)
1c009710:	00090023          	sb	zero,0(s2)
1c009714:	40f90933          	sub	s2,s2,a5
1c009718:	0147fd63          	bleu	s4,a5,1c009732 <pos_libc_prf+0x58e>
1c00971c:	105c                	addi	a5,sp,36
1c00971e:	0007c683          	lbu	a3,0(a5)
1c009722:	000a4703          	lbu	a4,0(s4)
1c009726:	feda0fab          	p.sb	a3,-1(s4!)
1c00972a:	00e780ab          	p.sb	a4,1(a5!)
1c00972e:	ff47e8e3          	bltu	a5,s4,1c00971e <pos_libc_prf+0x57a>
1c009732:	c202                	sw	zero,4(sp)
1c009734:	b9d5                	j	1c009428 <pos_libc_prf+0x284>
1c009736:	00b78023          	sb	a1,0(a5)
1c00973a:	00178593          	addi	a1,a5,1
1c00973e:	fd49                	bnez	a0,1c0096d8 <pos_libc_prf+0x534>
1c009740:	00058023          	sb	zero,0(a1) # 1a10f000 <__l1_end+0xa10efd0>
1c009744:	8d95                	sub	a1,a1,a3
1c009746:	00f6fc63          	bleu	a5,a3,1c00975e <pos_libc_prf+0x5ba>
1c00974a:	0006c603          	lbu	a2,0(a3)
1c00974e:	0007c703          	lbu	a4,0(a5)
1c009752:	fec78fab          	p.sb	a2,-1(a5!)
1c009756:	00e680ab          	p.sb	a4,1(a3!)
1c00975a:	fef6e8e3          	bltu	a3,a5,1c00974a <pos_libc_prf+0x5a6>
1c00975e:	05800793          	li	a5,88
1c009762:	28fd82e3          	beq	s11,a5,1c00a1e6 <pos_libc_prf+0x1042>
1c009766:	4712                	lw	a4,4(sp)
1c009768:	992e                	add	s2,s2,a1
1c00976a:	0706                	slli	a4,a4,0x1
1c00976c:	c23a                	sw	a4,4(sp)
1c00976e:	b96d                	j	1c009428 <pos_libc_prf+0x284>
1c009770:	4c81                	li	s9,0
1c009772:	cc02                	sw	zero,24(sp)
1c009774:	4a01                	li	s4,0
1c009776:	47d2                	lw	a5,20(sp)
1c009778:	5e078163          	beqz	a5,1c009d5a <pos_libc_prf+0xbb6>
1c00977c:	412b04b3          	sub	s1,s6,s2
1c009780:	0404e4b3          	p.max	s1,s1,zero
1c009784:	009907b3          	add	a5,s2,s1
1c009788:	40fb0b33          	sub	s6,s6,a5
1c00978c:	1040                	addi	s0,sp,36
1c00978e:	b96d                	j	1c009448 <pos_libc_prf+0x2a4>
1c009790:	4881                	li	a7,0
1c009792:	4801                	li	a6,0
1c009794:	4581                	li	a1,0
1c009796:	4501                	li	a0,0
1c009798:	4f11                	li	t5,4
1c00979a:	410f0f33          	sub	t5,t5,a6
1c00979e:	012f40fb          	lp.setup	x1,t5,1c0097c2 <pos_libc_prf+0x61e>
1c0097a2:	01f51713          	slli	a4,a0,0x1f
1c0097a6:	0015d793          	srli	a5,a1,0x1
1c0097aa:	8fd9                	or	a5,a5,a4
1c0097ac:	fc15b5b3          	p.bclr	a1,a1,30,1
1c0097b0:	00f58eb3          	add	t4,a1,a5
1c0097b4:	8105                	srli	a0,a0,0x1
1c0097b6:	00beb5b3          	sltu	a1,t4,a1
1c0097ba:	00a587b3          	add	a5,a1,a0
1c0097be:	853e                	mv	a0,a5
1c0097c0:	85f6                	mv	a1,t4
1c0097c2:	0805                	addi	a6,a6,1
1c0097c4:	0004d363          	bgez	s1,1c0097ca <pos_libc_prf+0x626>
1c0097c8:	4499                	li	s1,6
1c0097ca:	04700693          	li	a3,71
1c0097ce:	0cde0be3          	beq	t3,a3,1c00a0a4 <pos_libc_prf+0xf00>
1c0097d2:	06600693          	li	a3,102
1c0097d6:	4f81                	li	t6,0
1c0097d8:	0edd84e3          	beq	s11,a3,1c00a0c0 <pos_libc_prf+0xf1c>
1c0097dc:	00148f13          	addi	t5,s1,1
1c0097e0:	4741                	li	a4,16
1c0097e2:	04ef4f33          	p.min	t5,t5,a4
1c0097e6:	1f7d                	addi	t5,t5,-1
1c0097e8:	4501                	li	a0,0
1c0097ea:	080006b7          	lui	a3,0x8000
1c0097ee:	4295                	li	t0,5
1c0097f0:	0f05                	addi	t5,t5,1
1c0097f2:	030f40fb          	lp.setup	x1,t5,1c009852 <pos_libc_prf+0x6ae>
1c0097f6:	00250613          	addi	a2,a0,2
1c0097fa:	00a63733          	sltu	a4,a2,a0
1c0097fe:	9736                	add	a4,a4,a3
1c009800:	02575533          	divu	a0,a4,t0
1c009804:	00251693          	slli	a3,a0,0x2
1c009808:	96aa                	add	a3,a3,a0
1c00980a:	8f15                	sub	a4,a4,a3
1c00980c:	0776                	slli	a4,a4,0x1d
1c00980e:	00365593          	srli	a1,a2,0x3
1c009812:	8dd9                	or	a1,a1,a4
1c009814:	0255d5b3          	divu	a1,a1,t0
1c009818:	00359693          	slli	a3,a1,0x3
1c00981c:	00559713          	slli	a4,a1,0x5
1c009820:	9736                	add	a4,a4,a3
1c009822:	40e60733          	sub	a4,a2,a4
1c009826:	02575733          	divu	a4,a4,t0
1c00982a:	81f5                	srli	a1,a1,0x1d
1c00982c:	00d70633          	add	a2,a4,a3
1c009830:	95aa                	add	a1,a1,a0
1c009832:	00e63733          	sltu	a4,a2,a4
1c009836:	00b706b3          	add	a3,a4,a1
1c00983a:	01f69593          	slli	a1,a3,0x1f
1c00983e:	00165713          	srli	a4,a2,0x1
1c009842:	8f4d                	or	a4,a4,a1
1c009844:	fc163633          	p.bclr	a2,a2,30,1
1c009848:	00e60533          	add	a0,a2,a4
1c00984c:	8285                	srli	a3,a3,0x1
1c00984e:	00c53633          	sltu	a2,a0,a2
1c009852:	96b2                	add	a3,a3,a2
1c009854:	00ae85b3          	add	a1,t4,a0
1c009858:	96be                	add	a3,a3,a5
1c00985a:	01d5beb3          	sltu	t4,a1,t4
1c00985e:	96f6                	add	a3,a3,t4
1c009860:	f606b533          	p.bclr	a0,a3,27,0
1c009864:	87ae                	mv	a5,a1
1c009866:	c125                	beqz	a0,1c0098c6 <pos_libc_prf+0x722>
1c009868:	00258513          	addi	a0,a1,2
1c00986c:	00b537b3          	sltu	a5,a0,a1
1c009870:	96be                	add	a3,a3,a5
1c009872:	4e95                	li	t4,5
1c009874:	03d6de33          	divu	t3,a3,t4
1c009878:	002e1793          	slli	a5,t3,0x2
1c00987c:	97f2                	add	a5,a5,t3
1c00987e:	8e9d                	sub	a3,a3,a5
1c009880:	01d69793          	slli	a5,a3,0x1d
1c009884:	00355693          	srli	a3,a0,0x3
1c009888:	8edd                	or	a3,a3,a5
1c00988a:	03d6d6b3          	divu	a3,a3,t4
1c00988e:	00369593          	slli	a1,a3,0x3
1c009892:	00569793          	slli	a5,a3,0x5
1c009896:	97ae                	add	a5,a5,a1
1c009898:	40f507b3          	sub	a5,a0,a5
1c00989c:	03d7d7b3          	divu	a5,a5,t4
1c0098a0:	82f5                	srli	a3,a3,0x1d
1c0098a2:	95be                	add	a1,a1,a5
1c0098a4:	00f5b7b3          	sltu	a5,a1,a5
1c0098a8:	96f2                	add	a3,a3,t3
1c0098aa:	96be                	add	a3,a3,a5
1c0098ac:	01f69513          	slli	a0,a3,0x1f
1c0098b0:	0015d793          	srli	a5,a1,0x1
1c0098b4:	8fc9                	or	a5,a5,a0
1c0098b6:	fc15b5b3          	p.bclr	a1,a1,30,1
1c0098ba:	97ae                	add	a5,a5,a1
1c0098bc:	8285                	srli	a3,a3,0x1
1c0098be:	00b7b5b3          	sltu	a1,a5,a1
1c0098c2:	96ae                	add	a3,a3,a1
1c0098c4:	0885                	addi	a7,a7,1
1c0098c6:	06600593          	li	a1,102
1c0098ca:	00130513          	addi	a0,t1,1
1c0098ce:	1ebd82e3          	beq	s11,a1,1c00a2b2 <pos_libc_prf+0x110e>
1c0098d2:	01e7de13          	srli	t3,a5,0x1e
1c0098d6:	00279593          	slli	a1,a5,0x2
1c0098da:	00269813          	slli	a6,a3,0x2
1c0098de:	97ae                	add	a5,a5,a1
1c0098e0:	010e6833          	or	a6,t3,a6
1c0098e4:	00b7b5b3          	sltu	a1,a5,a1
1c0098e8:	96c2                	add	a3,a3,a6
1c0098ea:	96ae                	add	a3,a3,a1
1c0098ec:	0686                	slli	a3,a3,0x1
1c0098ee:	01f7d593          	srli	a1,a5,0x1f
1c0098f2:	8ecd                	or	a3,a3,a1
1c0098f4:	01c6d593          	srli	a1,a3,0x1c
1c0098f8:	882e                	mv	a6,a1
1c0098fa:	4712                	lw	a4,4(sp)
1c0098fc:	03058593          	addi	a1,a1,48
1c009900:	01003833          	snez	a6,a6
1c009904:	00b30023          	sb	a1,0(t1)
1c009908:	c7c6be33          	p.bclr	t3,a3,3,28
1c00990c:	00179593          	slli	a1,a5,0x1
1c009910:	410888b3          	sub	a7,a7,a6
1c009914:	0a0714e3          	bnez	a4,1c00a1bc <pos_libc_prf+0x1018>
1c009918:	8ca6                	mv	s9,s1
1c00991a:	3c905d63          	blez	s1,1c009cf4 <pos_libc_prf+0xb50>
1c00991e:	02e00693          	li	a3,46
1c009922:	00230793          	addi	a5,t1,2
1c009926:	00d300a3          	sb	a3,1(t1)
1c00992a:	00259693          	slli	a3,a1,0x2
1c00992e:	01e5d813          	srli	a6,a1,0x1e
1c009932:	002e1513          	slli	a0,t3,0x2
1c009936:	95b6                	add	a1,a1,a3
1c009938:	00a86533          	or	a0,a6,a0
1c00993c:	00d5b833          	sltu	a6,a1,a3
1c009940:	01c506b3          	add	a3,a0,t3
1c009944:	9836                	add	a6,a6,a3
1c009946:	0806                	slli	a6,a6,0x1
1c009948:	01f5d693          	srli	a3,a1,0x1f
1c00994c:	0106e833          	or	a6,a3,a6
1c009950:	01c85313          	srli	t1,a6,0x1c
1c009954:	03030313          	addi	t1,t1,48
1c009958:	100006b7          	lui	a3,0x10000
1c00995c:	fff68513          	addi	a0,a3,-1 # fffffff <__l1_heap_size+0xfff002f>
1c009960:	00678023          	sb	t1,0(a5)
1c009964:	00159e13          	slli	t3,a1,0x1
1c009968:	00a87833          	and	a6,a6,a0
1c00996c:	0014b463          	p.bneimm	s1,1,1c009974 <pos_libc_prf+0x7d0>
1c009970:	3d40106f          	j	1c00ad44 <pos_libc_prf+0x1ba0>
1c009974:	00359693          	slli	a3,a1,0x3
1c009978:	00281313          	slli	t1,a6,0x2
1c00997c:	01ee5e93          	srli	t4,t3,0x1e
1c009980:	01c685b3          	add	a1,a3,t3
1c009984:	006ee333          	or	t1,t4,t1
1c009988:	981a                	add	a6,a6,t1
1c00998a:	00d5b6b3          	sltu	a3,a1,a3
1c00998e:	96c2                	add	a3,a3,a6
1c009990:	0686                	slli	a3,a3,0x1
1c009992:	01f5d813          	srli	a6,a1,0x1f
1c009996:	00d866b3          	or	a3,a6,a3
1c00999a:	01c6d813          	srli	a6,a3,0x1c
1c00999e:	03080813          	addi	a6,a6,48 # 1a100030 <__l1_end+0xa100000>
1c0099a2:	010780a3          	sb	a6,1(a5)
1c0099a6:	ffe48c93          	addi	s9,s1,-2
1c0099aa:	00159313          	slli	t1,a1,0x1
1c0099ae:	8ee9                	and	a3,a3,a0
1c0099b0:	01904463          	bgtz	s9,1c0099b8 <pos_libc_prf+0x814>
1c0099b4:	3880106f          	j	1c00ad3c <pos_libc_prf+0x1b98>
1c0099b8:	01e35e13          	srli	t3,t1,0x1e
1c0099bc:	058e                	slli	a1,a1,0x3
1c0099be:	00269813          	slli	a6,a3,0x2
1c0099c2:	932e                	add	t1,t1,a1
1c0099c4:	010e6833          	or	a6,t3,a6
1c0099c8:	96c2                	add	a3,a3,a6
1c0099ca:	00b335b3          	sltu	a1,t1,a1
1c0099ce:	95b6                	add	a1,a1,a3
1c0099d0:	0586                	slli	a1,a1,0x1
1c0099d2:	01f35693          	srli	a3,t1,0x1f
1c0099d6:	8dd5                	or	a1,a1,a3
1c0099d8:	01c5d693          	srli	a3,a1,0x1c
1c0099dc:	03068693          	addi	a3,a3,48
1c0099e0:	00d78123          	sb	a3,2(a5)
1c0099e4:	ffd48c93          	addi	s9,s1,-3
1c0099e8:	00131e13          	slli	t3,t1,0x1
1c0099ec:	8de9                	and	a1,a1,a0
1c0099ee:	01904463          	bgtz	s9,1c0099f6 <pos_libc_prf+0x852>
1c0099f2:	3420106f          	j	1c00ad34 <pos_libc_prf+0x1b90>
1c0099f6:	00331693          	slli	a3,t1,0x3
1c0099fa:	00259813          	slli	a6,a1,0x2
1c0099fe:	01ee5313          	srli	t1,t3,0x1e
1c009a02:	01036833          	or	a6,t1,a6
1c009a06:	9e36                	add	t3,t3,a3
1c009a08:	95c2                	add	a1,a1,a6
1c009a0a:	00de36b3          	sltu	a3,t3,a3
1c009a0e:	96ae                	add	a3,a3,a1
1c009a10:	0686                	slli	a3,a3,0x1
1c009a12:	01fe5593          	srli	a1,t3,0x1f
1c009a16:	8ecd                	or	a3,a3,a1
1c009a18:	01c6d593          	srli	a1,a3,0x1c
1c009a1c:	03058593          	addi	a1,a1,48
1c009a20:	00b781a3          	sb	a1,3(a5)
1c009a24:	ffc48c93          	addi	s9,s1,-4
1c009a28:	001e1313          	slli	t1,t3,0x1
1c009a2c:	8ee9                	and	a3,a3,a0
1c009a2e:	01904463          	bgtz	s9,1c009a36 <pos_libc_prf+0x892>
1c009a32:	2fa0106f          	j	1c00ad2c <pos_libc_prf+0x1b88>
1c009a36:	003e1593          	slli	a1,t3,0x3
1c009a3a:	00269813          	slli	a6,a3,0x2
1c009a3e:	01e35e13          	srli	t3,t1,0x1e
1c009a42:	010e6833          	or	a6,t3,a6
1c009a46:	932e                	add	t1,t1,a1
1c009a48:	96c2                	add	a3,a3,a6
1c009a4a:	00b335b3          	sltu	a1,t1,a1
1c009a4e:	95b6                	add	a1,a1,a3
1c009a50:	0586                	slli	a1,a1,0x1
1c009a52:	01f35693          	srli	a3,t1,0x1f
1c009a56:	8dd5                	or	a1,a1,a3
1c009a58:	01c5d693          	srli	a3,a1,0x1c
1c009a5c:	03068693          	addi	a3,a3,48
1c009a60:	00d78223          	sb	a3,4(a5)
1c009a64:	ffb48c93          	addi	s9,s1,-5
1c009a68:	00131e13          	slli	t3,t1,0x1
1c009a6c:	8de9                	and	a1,a1,a0
1c009a6e:	01904463          	bgtz	s9,1c009a76 <pos_libc_prf+0x8d2>
1c009a72:	2b20106f          	j	1c00ad24 <pos_libc_prf+0x1b80>
1c009a76:	00331693          	slli	a3,t1,0x3
1c009a7a:	00259813          	slli	a6,a1,0x2
1c009a7e:	01ee5313          	srli	t1,t3,0x1e
1c009a82:	01036833          	or	a6,t1,a6
1c009a86:	9e36                	add	t3,t3,a3
1c009a88:	95c2                	add	a1,a1,a6
1c009a8a:	00de36b3          	sltu	a3,t3,a3
1c009a8e:	96ae                	add	a3,a3,a1
1c009a90:	0686                	slli	a3,a3,0x1
1c009a92:	01fe5593          	srli	a1,t3,0x1f
1c009a96:	8ecd                	or	a3,a3,a1
1c009a98:	01c6d593          	srli	a1,a3,0x1c
1c009a9c:	03058593          	addi	a1,a1,48
1c009aa0:	00b782a3          	sb	a1,5(a5)
1c009aa4:	ffa48c93          	addi	s9,s1,-6
1c009aa8:	001e1313          	slli	t1,t3,0x1
1c009aac:	8ee9                	and	a3,a3,a0
1c009aae:	01904463          	bgtz	s9,1c009ab6 <pos_libc_prf+0x912>
1c009ab2:	26a0106f          	j	1c00ad1c <pos_libc_prf+0x1b78>
1c009ab6:	003e1593          	slli	a1,t3,0x3
1c009aba:	00269813          	slli	a6,a3,0x2
1c009abe:	01e35e13          	srli	t3,t1,0x1e
1c009ac2:	010e6833          	or	a6,t3,a6
1c009ac6:	932e                	add	t1,t1,a1
1c009ac8:	96c2                	add	a3,a3,a6
1c009aca:	00b335b3          	sltu	a1,t1,a1
1c009ace:	95b6                	add	a1,a1,a3
1c009ad0:	0586                	slli	a1,a1,0x1
1c009ad2:	01f35693          	srli	a3,t1,0x1f
1c009ad6:	8dd5                	or	a1,a1,a3
1c009ad8:	01c5d693          	srli	a3,a1,0x1c
1c009adc:	03068693          	addi	a3,a3,48
1c009ae0:	00d78323          	sb	a3,6(a5)
1c009ae4:	ff948c93          	addi	s9,s1,-7
1c009ae8:	00131e13          	slli	t3,t1,0x1
1c009aec:	8de9                	and	a1,a1,a0
1c009aee:	01904463          	bgtz	s9,1c009af6 <pos_libc_prf+0x952>
1c009af2:	2220106f          	j	1c00ad14 <pos_libc_prf+0x1b70>
1c009af6:	00331693          	slli	a3,t1,0x3
1c009afa:	00259813          	slli	a6,a1,0x2
1c009afe:	01ee5313          	srli	t1,t3,0x1e
1c009b02:	01036833          	or	a6,t1,a6
1c009b06:	9e36                	add	t3,t3,a3
1c009b08:	95c2                	add	a1,a1,a6
1c009b0a:	00de36b3          	sltu	a3,t3,a3
1c009b0e:	96ae                	add	a3,a3,a1
1c009b10:	0686                	slli	a3,a3,0x1
1c009b12:	01fe5593          	srli	a1,t3,0x1f
1c009b16:	8ecd                	or	a3,a3,a1
1c009b18:	01c6d593          	srli	a1,a3,0x1c
1c009b1c:	03058593          	addi	a1,a1,48
1c009b20:	00b783a3          	sb	a1,7(a5)
1c009b24:	ff848c93          	addi	s9,s1,-8
1c009b28:	001e1313          	slli	t1,t3,0x1
1c009b2c:	8ee9                	and	a3,a3,a0
1c009b2e:	01904463          	bgtz	s9,1c009b36 <pos_libc_prf+0x992>
1c009b32:	1da0106f          	j	1c00ad0c <pos_libc_prf+0x1b68>
1c009b36:	003e1593          	slli	a1,t3,0x3
1c009b3a:	00269813          	slli	a6,a3,0x2
1c009b3e:	01e35e13          	srli	t3,t1,0x1e
1c009b42:	010e6833          	or	a6,t3,a6
1c009b46:	932e                	add	t1,t1,a1
1c009b48:	96c2                	add	a3,a3,a6
1c009b4a:	00b335b3          	sltu	a1,t1,a1
1c009b4e:	95b6                	add	a1,a1,a3
1c009b50:	0586                	slli	a1,a1,0x1
1c009b52:	01f35693          	srli	a3,t1,0x1f
1c009b56:	8dd5                	or	a1,a1,a3
1c009b58:	01c5d693          	srli	a3,a1,0x1c
1c009b5c:	03068693          	addi	a3,a3,48
1c009b60:	00d78423          	sb	a3,8(a5)
1c009b64:	ff748c93          	addi	s9,s1,-9
1c009b68:	00131e13          	slli	t3,t1,0x1
1c009b6c:	8de9                	and	a1,a1,a0
1c009b6e:	01904463          	bgtz	s9,1c009b76 <pos_libc_prf+0x9d2>
1c009b72:	1920106f          	j	1c00ad04 <pos_libc_prf+0x1b60>
1c009b76:	00331693          	slli	a3,t1,0x3
1c009b7a:	00259813          	slli	a6,a1,0x2
1c009b7e:	01ee5e93          	srli	t4,t3,0x1e
1c009b82:	01c68333          	add	t1,a3,t3
1c009b86:	010ee833          	or	a6,t4,a6
1c009b8a:	982e                	add	a6,a6,a1
1c009b8c:	00d336b3          	sltu	a3,t1,a3
1c009b90:	96c2                	add	a3,a3,a6
1c009b92:	01f35593          	srli	a1,t1,0x1f
1c009b96:	0686                	slli	a3,a3,0x1
1c009b98:	8ecd                	or	a3,a3,a1
1c009b9a:	01c6d593          	srli	a1,a3,0x1c
1c009b9e:	03058593          	addi	a1,a1,48
1c009ba2:	00b784a3          	sb	a1,9(a5)
1c009ba6:	ff648c93          	addi	s9,s1,-10
1c009baa:	8ee9                	and	a3,a3,a0
1c009bac:	00131593          	slli	a1,t1,0x1
1c009bb0:	00a78513          	addi	a0,a5,10
1c009bb4:	15905063          	blez	s9,1c009cf4 <pos_libc_prf+0xb50>
1c009bb8:	00259513          	slli	a0,a1,0x2
1c009bbc:	01e5d813          	srli	a6,a1,0x1e
1c009bc0:	00269313          	slli	t1,a3,0x2
1c009bc4:	95aa                	add	a1,a1,a0
1c009bc6:	00686333          	or	t1,a6,t1
1c009bca:	969a                	add	a3,a3,t1
1c009bcc:	00a5b833          	sltu	a6,a1,a0
1c009bd0:	9836                	add	a6,a6,a3
1c009bd2:	0806                	slli	a6,a6,0x1
1c009bd4:	01f5d693          	srli	a3,a1,0x1f
1c009bd8:	0106e833          	or	a6,a3,a6
1c009bdc:	01c85313          	srli	t1,a6,0x1c
1c009be0:	03030313          	addi	t1,t1,48
1c009be4:	100006b7          	lui	a3,0x10000
1c009be8:	fff68513          	addi	a0,a3,-1 # fffffff <__l1_heap_size+0xfff002f>
1c009bec:	00678523          	sb	t1,10(a5)
1c009bf0:	ff548c93          	addi	s9,s1,-11
1c009bf4:	00159e13          	slli	t3,a1,0x1
1c009bf8:	00a87833          	and	a6,a6,a0
1c009bfc:	01904463          	bgtz	s9,1c009c04 <pos_libc_prf+0xa60>
1c009c00:	0fc0106f          	j	1c00acfc <pos_libc_prf+0x1b58>
1c009c04:	00359693          	slli	a3,a1,0x3
1c009c08:	00281313          	slli	t1,a6,0x2
1c009c0c:	01ee5e93          	srli	t4,t3,0x1e
1c009c10:	01c685b3          	add	a1,a3,t3
1c009c14:	006ee333          	or	t1,t4,t1
1c009c18:	981a                	add	a6,a6,t1
1c009c1a:	00d5b6b3          	sltu	a3,a1,a3
1c009c1e:	96c2                	add	a3,a3,a6
1c009c20:	0686                	slli	a3,a3,0x1
1c009c22:	01f5d813          	srli	a6,a1,0x1f
1c009c26:	00d866b3          	or	a3,a6,a3
1c009c2a:	01c6d813          	srli	a6,a3,0x1c
1c009c2e:	03080813          	addi	a6,a6,48
1c009c32:	010785a3          	sb	a6,11(a5)
1c009c36:	ff448c93          	addi	s9,s1,-12
1c009c3a:	00159313          	slli	t1,a1,0x1
1c009c3e:	8ee9                	and	a3,a3,a0
1c009c40:	01904463          	bgtz	s9,1c009c48 <pos_libc_prf+0xaa4>
1c009c44:	0b00106f          	j	1c00acf4 <pos_libc_prf+0x1b50>
1c009c48:	058e                	slli	a1,a1,0x3
1c009c4a:	01e35e13          	srli	t3,t1,0x1e
1c009c4e:	00269813          	slli	a6,a3,0x2
1c009c52:	932e                	add	t1,t1,a1
1c009c54:	010e6833          	or	a6,t3,a6
1c009c58:	96c2                	add	a3,a3,a6
1c009c5a:	00b335b3          	sltu	a1,t1,a1
1c009c5e:	95b6                	add	a1,a1,a3
1c009c60:	0586                	slli	a1,a1,0x1
1c009c62:	01f35693          	srli	a3,t1,0x1f
1c009c66:	8dd5                	or	a1,a1,a3
1c009c68:	01c5d693          	srli	a3,a1,0x1c
1c009c6c:	03068693          	addi	a3,a3,48
1c009c70:	00d78623          	sb	a3,12(a5)
1c009c74:	ff348c93          	addi	s9,s1,-13
1c009c78:	00131813          	slli	a6,t1,0x1
1c009c7c:	01904463          	bgtz	s9,1c009c84 <pos_libc_prf+0xae0>
1c009c80:	06c0106f          	j	1c00acec <pos_libc_prf+0x1b48>
1c009c84:	8de9                	and	a1,a1,a0
1c009c86:	00331693          	slli	a3,t1,0x3
1c009c8a:	01e85e13          	srli	t3,a6,0x1e
1c009c8e:	00259313          	slli	t1,a1,0x2
1c009c92:	9836                	add	a6,a6,a3
1c009c94:	006e6333          	or	t1,t3,t1
1c009c98:	959a                	add	a1,a1,t1
1c009c9a:	00d836b3          	sltu	a3,a6,a3
1c009c9e:	96ae                	add	a3,a3,a1
1c009ca0:	0686                	slli	a3,a3,0x1
1c009ca2:	01f85593          	srli	a1,a6,0x1f
1c009ca6:	8ecd                	or	a3,a3,a1
1c009ca8:	01c6d593          	srli	a1,a3,0x1c
1c009cac:	03058593          	addi	a1,a1,48
1c009cb0:	00b786a3          	sb	a1,13(a5)
1c009cb4:	ff248c93          	addi	s9,s1,-14
1c009cb8:	8ee9                	and	a3,a3,a0
1c009cba:	00181593          	slli	a1,a6,0x1
1c009cbe:	00e78513          	addi	a0,a5,14
1c009cc2:	03905963          	blez	s9,1c009cf4 <pos_libc_prf+0xb50>
1c009cc6:	00381513          	slli	a0,a6,0x3
1c009cca:	01e5d313          	srli	t1,a1,0x1e
1c009cce:	00269813          	slli	a6,a3,0x2
1c009cd2:	95aa                	add	a1,a1,a0
1c009cd4:	01036833          	or	a6,t1,a6
1c009cd8:	00a5b5b3          	sltu	a1,a1,a0
1c009cdc:	96c2                	add	a3,a3,a6
1c009cde:	96ae                	add	a3,a3,a1
1c009ce0:	0686                	slli	a3,a3,0x1
1c009ce2:	82f1                	srli	a3,a3,0x1c
1c009ce4:	03068693          	addi	a3,a3,48
1c009ce8:	00f78513          	addi	a0,a5,15
1c009cec:	00d78723          	sb	a3,14(a5)
1c009cf0:	ff148c93          	addi	s9,s1,-15
1c009cf4:	440f8563          	beqz	t6,1c00a13e <pos_libc_prf+0xf9a>
1c009cf8:	4581                	li	a1,0
1c009cfa:	cc02                	sw	zero,24(sp)
1c009cfc:	4a01                	li	s4,0
1c009cfe:	03000813          	li	a6,48
1c009d02:	a011                	j	1c009d06 <pos_libc_prf+0xb62>
1c009d04:	853e                	mv	a0,a5
1c009d06:	fff50793          	addi	a5,a0,-1
1c009d0a:	0007c683          	lbu	a3,0(a5)
1c009d0e:	ff068be3          	beq	a3,a6,1c009d04 <pos_libc_prf+0xb60>
1c009d12:	02e00813          	li	a6,46
1c009d16:	4c81                	li	s9,0
1c009d18:	01069363          	bne	a3,a6,1c009d1e <pos_libc_prf+0xb7a>
1c009d1c:	853e                	mv	a0,a5
1c009d1e:	0dfdf793          	andi	a5,s11,223
1c009d22:	04500693          	li	a3,69
1c009d26:	3ad78e63          	beq	a5,a3,1c00a0e2 <pos_libc_prf+0xf3e>
1c009d2a:	4782                	lw	a5,0(sp)
1c009d2c:	00050023          	sb	zero,0(a0)
1c009d30:	8d1d                	sub	a0,a0,a5
1c009d32:	4732                	lw	a4,12(sp)
1c009d34:	2a071263          	bnez	a4,1c009fd8 <pos_libc_prf+0xe34>
1c009d38:	47c2                	lw	a5,16(sp)
1c009d3a:	28079f63          	bnez	a5,1c009fd8 <pos_libc_prf+0xe34>
1c009d3e:	02414783          	lbu	a5,36(sp)
1c009d42:	02d00693          	li	a3,45
1c009d46:	c202                	sw	zero,4(sp)
1c009d48:	28d78863          	beq	a5,a3,1c009fd8 <pos_libc_prf+0xe34>
1c009d4c:	fd078793          	addi	a5,a5,-48
1c009d50:	46a5                	li	a3,9
1c009d52:	00b50933          	add	s2,a0,a1
1c009d56:	a2f6f0e3          	bleu	a5,a3,1c009776 <pos_libc_prf+0x5d2>
1c009d5a:	412b0b33          	sub	s6,s6,s2
1c009d5e:	1040                	addi	s0,sp,36
1c009d60:	4481                	li	s1,0
1c009d62:	ee6ff06f          	j	1c009448 <pos_libc_prf+0x2a4>
1c009d66:	000a2783          	lw	a5,0(s4)
1c009d6a:	0a11                	addi	s4,s4,4
1c009d6c:	ce52                	sw	s4,28(sp)
1c009d6e:	02f10223          	sb	a5,36(sp)
1c009d72:	1b7d                	addi	s6,s6,-1
1c009d74:	4481                	li	s1,0
1c009d76:	c202                	sw	zero,4(sp)
1c009d78:	4905                	li	s2,1
1c009d7a:	1040                	addi	s0,sp,36
1c009d7c:	ec6ff06f          	j	1c009442 <pos_libc_prf+0x29e>
1c009d80:	04c00613          	li	a2,76
1c009d84:	004a268b          	p.lw	a3,4(s4!)
1c009d88:	5ac78ee3          	beq	a5,a2,1c00ab44 <pos_libc_prf+0x19a0>
1c009d8c:	28f65363          	ble	a5,a2,1c00a012 <pos_libc_prf+0xe6e>
1c009d90:	06800613          	li	a2,104
1c009d94:	00c78663          	beq	a5,a2,1c009da0 <pos_libc_prf+0xbfc>
1c009d98:	0156a023          	sw	s5,0(a3)
1c009d9c:	c46ff06f          	j	1c0091e2 <pos_libc_prf+0x3e>
1c009da0:	87d6                	mv	a5,s5
1c009da2:	00f69023          	sh	a5,0(a3)
1c009da6:	c3cff06f          	j	1c0091e2 <pos_libc_prf+0x3e>
1c009daa:	004a0793          	addi	a5,s4,4
1c009dae:	7761                	lui	a4,0xffff8
1c009db0:	02610593          	addi	a1,sp,38
1c009db4:	ce3e                	sw	a5,28(sp)
1c009db6:	83074713          	xori	a4,a4,-2000
1c009dba:	000a2783          	lw	a5,0(s4)
1c009dbe:	4601                	li	a2,0
1c009dc0:	02e11223          	sh	a4,36(sp)
1c009dc4:	86ae                	mv	a3,a1
1c009dc6:	4ea5                	li	t4,9
1c009dc8:	f647b733          	p.bclr	a4,a5,27,4
1c009dcc:	01c61513          	slli	a0,a2,0x1c
1c009dd0:	8391                	srli	a5,a5,0x4
1c009dd2:	8fc9                	or	a5,a5,a0
1c009dd4:	8211                	srli	a2,a2,0x4
1c009dd6:	05770e13          	addi	t3,a4,87 # ffff8057 <pulp__FC+0xffff8058>
1c009dda:	03070893          	addi	a7,a4,48
1c009dde:	00c7e333          	or	t1,a5,a2
1c009de2:	00eefa63          	bleu	a4,t4,1c009df6 <pos_libc_prf+0xc52>
1c009de6:	01c68023          	sb	t3,0(a3)
1c009dea:	00168513          	addi	a0,a3,1
1c009dee:	00030a63          	beqz	t1,1c009e02 <pos_libc_prf+0xc5e>
1c009df2:	86aa                	mv	a3,a0
1c009df4:	bfd1                	j	1c009dc8 <pos_libc_prf+0xc24>
1c009df6:	01168023          	sb	a7,0(a3)
1c009dfa:	00168513          	addi	a0,a3,1
1c009dfe:	fe031ae3          	bnez	t1,1c009df2 <pos_libc_prf+0xc4e>
1c009e02:	00050023          	sb	zero,0(a0)
1c009e06:	8d0d                	sub	a0,a0,a1
1c009e08:	00d5fe63          	bleu	a3,a1,1c009e24 <pos_libc_prf+0xc80>
1c009e0c:	87b6                	mv	a5,a3
1c009e0e:	86ae                	mv	a3,a1
1c009e10:	0006c603          	lbu	a2,0(a3)
1c009e14:	0007c703          	lbu	a4,0(a5)
1c009e18:	fec78fab          	p.sb	a2,-1(a5!)
1c009e1c:	00e680ab          	p.sb	a4,1(a3!)
1c009e20:	fef6e8e3          	bltu	a3,a5,1c009e10 <pos_libc_prf+0xc6c>
1c009e24:	4789                	li	a5,2
1c009e26:	00250913          	addi	s2,a0,2
1c009e2a:	c23e                	sw	a5,4(sp)
1c009e2c:	dfcff06f          	j	1c009428 <pos_libc_prf+0x284>
1c009e30:	85de                	mv	a1,s7
1c009e32:	02500513          	li	a0,37
1c009e36:	9982                	jalr	s3
1c009e38:	cff52163          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c009e3c:	85de                	mv	a1,s7
1c009e3e:	856e                	mv	a0,s11
1c009e40:	9982                	jalr	s3
1c009e42:	cdf52c63          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c009e46:	0a89                	addi	s5,s5,2
1c009e48:	b9aff06f          	j	1c0091e2 <pos_libc_prf+0x3e>
1c009e4c:	007a0893          	addi	a7,s4,7
1c009e50:	c408b8b3          	p.bclr	a7,a7,2,0
1c009e54:	0008a783          	lw	a5,0(a7)
1c009e58:	0048a303          	lw	t1,4(a7)
1c009e5c:	0157d693          	srli	a3,a5,0x15
1c009e60:	00b31513          	slli	a0,t1,0xb
1c009e64:	08a1                	addi	a7,a7,8
1c009e66:	01435813          	srli	a6,t1,0x14
1c009e6a:	8d55                	or	a0,a0,a3
1c009e6c:	ce46                	sw	a7,28(sp)
1c009e6e:	e8b83833          	p.bclr	a6,a6,20,11
1c009e72:	00b79593          	slli	a1,a5,0xb
1c009e76:	c1f53533          	p.bclr	a0,a0,0,31
1c009e7a:	1e034e63          	bltz	t1,1c00a076 <pos_libc_prf+0xed2>
1c009e7e:	47b2                	lw	a5,12(sp)
1c009e80:	1c078f63          	beqz	a5,1c00a05e <pos_libc_prf+0xeba>
1c009e84:	02b00793          	li	a5,43
1c009e88:	02f10223          	sb	a5,36(sp)
1c009e8c:	02510313          	addi	t1,sp,37
1c009e90:	7ff00793          	li	a5,2047
1c009e94:	18f80863          	beq	a6,a5,1c00a024 <pos_libc_prf+0xe80>
1c009e98:	04600793          	li	a5,70
1c009e9c:	0dfdfe13          	andi	t3,s11,223
1c009ea0:	32fd8e63          	beq	s11,a5,1c00a1dc <pos_libc_prf+0x1038>
1c009ea4:	41f85693          	srai	a3,a6,0x1f
1c009ea8:	00b867b3          	or	a5,a6,a1
1c009eac:	8ec9                	or	a3,a3,a0
1c009eae:	8fd5                	or	a5,a5,a3
1c009eb0:	8e0780e3          	beqz	a5,1c009790 <pos_libc_prf+0x5ec>
1c009eb4:	02081363          	bnez	a6,1c009eda <pos_libc_prf+0xd36>
1c009eb8:	01f5d793          	srli	a5,a1,0x1f
1c009ebc:	00151693          	slli	a3,a0,0x1
1c009ec0:	00d7e533          	or	a0,a5,a3
1c009ec4:	0586                	slli	a1,a1,0x1
1c009ec6:	5a054fe3          	bltz	a0,1c00ac84 <pos_libc_prf+0x1ae0>
1c009eca:	01f5d793          	srli	a5,a1,0x1f
1c009ece:	0506                	slli	a0,a0,0x1
1c009ed0:	8d5d                	or	a0,a0,a5
1c009ed2:	187d                	addi	a6,a6,-1
1c009ed4:	0586                	slli	a1,a1,0x1
1c009ed6:	fe055ae3          	bgez	a0,1c009eca <pos_libc_prf+0xd26>
1c009eda:	c0280813          	addi	a6,a6,-1022
1c009ede:	57f9                	li	a5,-2
1c009ee0:	c1f54533          	p.bset	a0,a0,0,31
1c009ee4:	4881                	li	a7,0
1c009ee6:	06f85763          	ble	a5,a6,1c009f54 <pos_libc_prf+0xdb0>
1c009eea:	33333eb7          	lui	t4,0x33333
1c009eee:	80000f37          	lui	t5,0x80000
1c009ef2:	4881                	li	a7,0
1c009ef4:	332e8e93          	addi	t4,t4,818 # 33333332 <__l2_shared_end+0x1732317e>
1c009ef8:	ffff4f13          	not	t5,t5
1c009efc:	5ff9                	li	t6,-2
1c009efe:	a011                	j	1c009f02 <pos_libc_prf+0xd5e>
1c009f00:	883e                	mv	a6,a5
1c009f02:	01f51693          	slli	a3,a0,0x1f
1c009f06:	0015d713          	srli	a4,a1,0x1
1c009f0a:	fc15b7b3          	p.bclr	a5,a1,30,1
1c009f0e:	8f55                	or	a4,a4,a3
1c009f10:	00e785b3          	add	a1,a5,a4
1c009f14:	00f5b7b3          	sltu	a5,a1,a5
1c009f18:	8105                	srli	a0,a0,0x1
1c009f1a:	953e                	add	a0,a0,a5
1c009f1c:	00180793          	addi	a5,a6,1
1c009f20:	feaee0e3          	bltu	t4,a0,1c009f00 <pos_libc_prf+0xd5c>
1c009f24:	00259693          	slli	a3,a1,0x2
1c009f28:	01e5d613          	srli	a2,a1,0x1e
1c009f2c:	00251713          	slli	a4,a0,0x2
1c009f30:	95b6                	add	a1,a1,a3
1c009f32:	8f51                	or	a4,a4,a2
1c009f34:	953a                	add	a0,a0,a4
1c009f36:	00d5b6b3          	sltu	a3,a1,a3
1c009f3a:	9536                	add	a0,a0,a3
1c009f3c:	01f5d713          	srli	a4,a1,0x1f
1c009f40:	0809                	addi	a6,a6,2
1c009f42:	18fd                	addi	a7,a7,-1
1c009f44:	01e51663          	bne	a0,t5,1c009f50 <pos_libc_prf+0xdac>
1c009f48:	0586                	slli	a1,a1,0x1
1c009f4a:	fc174533          	p.bset	a0,a4,30,1
1c009f4e:	883e                	mv	a6,a5
1c009f50:	fbf849e3          	blt	a6,t6,1c009f02 <pos_libc_prf+0xd5e>
1c009f54:	80000f37          	lui	t5,0x80000
1c009f58:	4f95                	li	t6,5
1c009f5a:	ffff4f13          	not	t5,t5
1c009f5e:	83005de3          	blez	a6,1c009798 <pos_libc_prf+0x5f4>
1c009f62:	00258693          	addi	a3,a1,2
1c009f66:	00b6b5b3          	sltu	a1,a3,a1
1c009f6a:	952e                	add	a0,a0,a1
1c009f6c:	03f557b3          	divu	a5,a0,t6
1c009f70:	00279713          	slli	a4,a5,0x2
1c009f74:	973e                	add	a4,a4,a5
1c009f76:	8d19                	sub	a0,a0,a4
1c009f78:	01d51713          	slli	a4,a0,0x1d
1c009f7c:	0036d613          	srli	a2,a3,0x3
1c009f80:	8e59                	or	a2,a2,a4
1c009f82:	03f65633          	divu	a2,a2,t6
1c009f86:	00361593          	slli	a1,a2,0x3
1c009f8a:	00561713          	slli	a4,a2,0x5
1c009f8e:	972e                	add	a4,a4,a1
1c009f90:	40e68733          	sub	a4,a3,a4
1c009f94:	03f75733          	divu	a4,a4,t6
1c009f98:	8275                	srli	a2,a2,0x1d
1c009f9a:	95ba                	add	a1,a1,a4
1c009f9c:	97b2                	add	a5,a5,a2
1c009f9e:	00e5b733          	sltu	a4,a1,a4
1c009fa2:	00f70533          	add	a0,a4,a5
1c009fa6:	187d                	addi	a6,a6,-1
1c009fa8:	0885                	addi	a7,a7,1
1c009faa:	01f5d793          	srli	a5,a1,0x1f
1c009fae:	0506                	slli	a0,a0,0x1
1c009fb0:	8d5d                	or	a0,a0,a5
1c009fb2:	0586                	slli	a1,a1,0x1
1c009fb4:	187d                	addi	a6,a6,-1
1c009fb6:	feaf7ae3          	bleu	a0,t5,1c009faa <pos_libc_prf+0xe06>
1c009fba:	b755                	j	1c009f5e <pos_libc_prf+0xdba>
1c009fbc:	001d4d83          	lbu	s11,1(s10)
1c009fc0:	04c00793          	li	a5,76
1c009fc4:	0d09                	addi	s10,s10,2
1c009fc6:	ad6ff06f          	j	1c00929c <pos_libc_prf+0xf8>
1c009fca:	001d4d83          	lbu	s11,1(s10)
1c009fce:	04800793          	li	a5,72
1c009fd2:	0d09                	addi	s10,s10,2
1c009fd4:	ac8ff06f          	j	1c00929c <pos_libc_prf+0xf8>
1c009fd8:	4705                	li	a4,1
1c009fda:	02514783          	lbu	a5,37(sp)
1c009fde:	c23a                	sw	a4,4(sp)
1c009fe0:	b3b5                	j	1c009d4c <pos_libc_prf+0xba8>
1c009fe2:	004a0793          	addi	a5,s4,4
1c009fe6:	ce3e                	sw	a5,28(sp)
1c009fe8:	000a2403          	lw	s0,0(s4)
1c009fec:	4c81                	li	s9,0
1c009fee:	e92ff06f          	j	1c009680 <pos_libc_prf+0x4dc>
1c009ff2:	4785                	li	a5,1
1c009ff4:	c23e                	sw	a5,4(sp)
1c009ff6:	c32ff06f          	j	1c009428 <pos_libc_prf+0x284>
1c009ffa:	4742                	lw	a4,16(sp)
1c009ffc:	22070063          	beqz	a4,1c00a21c <pos_libc_prf+0x1078>
1c00a000:	02000693          	li	a3,32
1c00a004:	02d10223          	sb	a3,36(sp)
1c00a008:	4c92                	lw	s9,4(sp)
1c00a00a:	02510a13          	addi	s4,sp,37
1c00a00e:	bacff06f          	j	1c0093ba <pos_libc_prf+0x216>
1c00a012:	04800613          	li	a2,72
1c00a016:	d8c791e3          	bne	a5,a2,1c009d98 <pos_libc_prf+0xbf4>
1c00a01a:	87d6                	mv	a5,s5
1c00a01c:	00f68023          	sb	a5,0(a3)
1c00a020:	9c2ff06f          	j	1c0091e2 <pos_libc_prf+0x3e>
1c00a024:	00a5e6b3          	or	a3,a1,a0
1c00a028:	fbfd8613          	addi	a2,s11,-65
1c00a02c:	00330513          	addi	a0,t1,3
1c00a030:	47e5                	li	a5,25
1c00a032:	16069963          	bnez	a3,1c00a1a4 <pos_libc_prf+0x1000>
1c00a036:	3ec7e1e3          	bltu	a5,a2,1c00ac18 <pos_libc_prf+0x1a74>
1c00a03a:	6795                	lui	a5,0x5
1c00a03c:	e4978793          	addi	a5,a5,-439 # 4e49 <pos_soc_event_callback+0x4a01>
1c00a040:	00f31023          	sh	a5,0(t1)
1c00a044:	04600793          	li	a5,70
1c00a048:	00f30123          	sb	a5,2(t1)
1c00a04c:	4782                	lw	a5,0(sp)
1c00a04e:	000301a3          	sb	zero,3(t1)
1c00a052:	8d1d                	sub	a0,a0,a5
1c00a054:	4581                	li	a1,0
1c00a056:	4c81                	li	s9,0
1c00a058:	cc02                	sw	zero,24(sp)
1c00a05a:	4a01                	li	s4,0
1c00a05c:	b9d9                	j	1c009d32 <pos_libc_prf+0xb8e>
1c00a05e:	4742                	lw	a4,16(sp)
1c00a060:	02410313          	addi	t1,sp,36
1c00a064:	e20706e3          	beqz	a4,1c009e90 <pos_libc_prf+0xcec>
1c00a068:	02000793          	li	a5,32
1c00a06c:	02f10223          	sb	a5,36(sp)
1c00a070:	02510313          	addi	t1,sp,37
1c00a074:	bd31                	j	1c009e90 <pos_libc_prf+0xcec>
1c00a076:	02d00793          	li	a5,45
1c00a07a:	02f10223          	sb	a5,36(sp)
1c00a07e:	02510313          	addi	t1,sp,37
1c00a082:	b539                	j	1c009e90 <pos_libc_prf+0xcec>
1c00a084:	40f007b3          	neg	a5,a5
1c00a088:	00f036b3          	snez	a3,a5
1c00a08c:	40e00cb3          	neg	s9,a4
1c00a090:	02d00613          	li	a2,45
1c00a094:	02c10223          	sb	a2,36(sp)
1c00a098:	40dc8cb3          	sub	s9,s9,a3
1c00a09c:	02510a13          	addi	s4,sp,37
1c00a0a0:	b1aff06f          	j	1c0093ba <pos_libc_prf+0x216>
1c00a0a4:	56f5                	li	a3,-3
1c00a0a6:	0cd8c063          	blt	a7,a3,1c00a166 <pos_libc_prf+0xfc2>
1c00a0aa:	0b14ce63          	blt	s1,a7,1c00a166 <pos_libc_prf+0xfc2>
1c00a0ae:	4712                	lw	a4,4(sp)
1c00a0b0:	411484b3          	sub	s1,s1,a7
1c00a0b4:	4f81                	li	t6,0
1c00a0b6:	e709                	bnez	a4,1c00a0c0 <pos_libc_prf+0xf1c>
1c00a0b8:	00902fb3          	sgtz	t6,s1
1c00a0bc:	0fffff93          	andi	t6,t6,255
1c00a0c0:	009886b3          	add	a3,a7,s1
1c00a0c4:	2e06cae3          	bltz	a3,1c00abb8 <pos_libc_prf+0x1a14>
1c00a0c8:	4741                	li	a4,16
1c00a0ca:	04e6cf33          	p.min	t5,a3,a4
1c00a0ce:	1f7d                	addi	t5,t5,-1
1c00a0d0:	06600d93          	li	s11,102
1c00a0d4:	f0069a63          	bnez	a3,1c0097e8 <pos_libc_prf+0x644>
1c00a0d8:	4501                	li	a0,0
1c00a0da:	080006b7          	lui	a3,0x8000
1c00a0de:	f76ff06f          	j	1c009854 <pos_libc_prf+0x6b0>
1c00a0e2:	86aa                	mv	a3,a0
1c00a0e4:	01b6812b          	p.sb	s11,2(a3!) # 8000002 <__l1_heap_size+0x7ff0032>
1c00a0e8:	2408c6e3          	bltz	a7,1c00ab34 <pos_libc_prf+0x1990>
1c00a0ec:	02b00793          	li	a5,43
1c00a0f0:	00f500a3          	sb	a5,1(a0)
1c00a0f4:	06300793          	li	a5,99
1c00a0f8:	0117de63          	ble	a7,a5,1c00a114 <pos_libc_prf+0xf70>
1c00a0fc:	06400693          	li	a3,100
1c00a100:	02d8c7b3          	div	a5,a7,a3
1c00a104:	03078793          	addi	a5,a5,48
1c00a108:	02d8e8b3          	rem	a7,a7,a3
1c00a10c:	00f50123          	sb	a5,2(a0)
1c00a110:	00350693          	addi	a3,a0,3
1c00a114:	47a9                	li	a5,10
1c00a116:	02f8c633          	div	a2,a7,a5
1c00a11a:	02f8e7b3          	rem	a5,a7,a5
1c00a11e:	03060613          	addi	a2,a2,48 # 1a100030 <__l1_end+0xa100000>
1c00a122:	8536                	mv	a0,a3
1c00a124:	00c5012b          	p.sb	a2,2(a0!)
1c00a128:	03078793          	addi	a5,a5,48
1c00a12c:	00f680a3          	sb	a5,1(a3)
1c00a130:	beed                	j	1c009d2a <pos_libc_prf+0xb86>
1c00a132:	800004b7          	lui	s1,0x80000
1c00a136:	fff4c493          	not	s1,s1
1c00a13a:	c3cff06f          	j	1c009576 <pos_libc_prf+0x3d2>
1c00a13e:	85e6                	mv	a1,s9
1c00a140:	cc02                	sw	zero,24(sp)
1c00a142:	4a01                	li	s4,0
1c00a144:	bee9                	j	1c009d1e <pos_libc_prf+0xb7a>
1c00a146:	4901                	li	s2,0
1c00a148:	1054                	addi	a3,sp,36
1c00a14a:	d60ff06f          	j	1c0096aa <pos_libc_prf+0x506>
1c00a14e:	007a0793          	addi	a5,s4,7
1c00a152:	c407b7b3          	p.bclr	a5,a5,2,0
1c00a156:	00878713          	addi	a4,a5,8
1c00a15a:	ce3a                	sw	a4,28(sp)
1c00a15c:	4380                	lw	s0,0(a5)
1c00a15e:	0047ac83          	lw	s9,4(a5)
1c00a162:	d1eff06f          	j	1c009680 <pos_libc_prf+0x4dc>
1c00a166:	ffed8613          	addi	a2,s11,-2
1c00a16a:	0ff67d93          	andi	s11,a2,255
1c00a16e:	220486e3          	beqz	s1,1c00ab9a <pos_libc_prf+0x19f6>
1c00a172:	4712                	lw	a4,4(sp)
1c00a174:	fff48693          	addi	a3,s1,-1 # 7fffffff <pulp__FC+0x80000000>
1c00a178:	1e071fe3          	bnez	a4,1c00ab76 <pos_libc_prf+0x19d2>
1c00a17c:	00d02fb3          	sgtz	t6,a3
1c00a180:	0fffff93          	andi	t6,t6,255
1c00a184:	84b6                	mv	s1,a3
1c00a186:	e56ff06f          	j	1c0097dc <pos_libc_prf+0x638>
1c00a18a:	007a0693          	addi	a3,s4,7
1c00a18e:	c406b6b3          	p.bclr	a3,a3,2,0
1c00a192:	00868793          	addi	a5,a3,8
1c00a196:	ce3e                	sw	a5,28(sp)
1c00a198:	429c                	lw	a5,0(a3)
1c00a19a:	42d4                	lw	a3,4(a3)
1c00a19c:	c236                	sw	a3,4(sp)
1c00a19e:	8736                	mv	a4,a3
1c00a1a0:	a02ff06f          	j	1c0093a2 <pos_libc_prf+0x1fe>
1c00a1a4:	24c7efe3          	bltu	a5,a2,1c00ac02 <pos_libc_prf+0x1a5e>
1c00a1a8:	6791                	lui	a5,0x4
1c00a1aa:	14e78793          	addi	a5,a5,334 # 414e <pos_soc_event_callback+0x3d06>
1c00a1ae:	00f31023          	sh	a5,0(t1)
1c00a1b2:	04e00793          	li	a5,78
1c00a1b6:	00f30123          	sb	a5,2(t1)
1c00a1ba:	bd49                	j	1c00a04c <pos_libc_prf+0xea8>
1c00a1bc:	02e00793          	li	a5,46
1c00a1c0:	00f300a3          	sb	a5,1(t1)
1c00a1c4:	00230793          	addi	a5,t1,2
1c00a1c8:	f6904163          	bgtz	s1,1c00992a <pos_libc_prf+0x786>
1c00a1cc:	8ca6                	mv	s9,s1
1c00a1ce:	853e                	mv	a0,a5
1c00a1d0:	b615                	j	1c009cf4 <pos_libc_prf+0xb50>
1c00a1d2:	4481                	li	s1,0
1c00a1d4:	c202                	sw	zero,4(sp)
1c00a1d6:	4901                	li	s2,0
1c00a1d8:	a6aff06f          	j	1c009442 <pos_libc_prf+0x29e>
1c00a1dc:	04600e13          	li	t3,70
1c00a1e0:	06600d93          	li	s11,102
1c00a1e4:	b1c1                	j	1c009ea4 <pos_libc_prf+0xd00>
1c00a1e6:	105c                	addi	a5,sp,36
1c00a1e8:	4565                	li	a0,25
1c00a1ea:	0017c70b          	p.lbu	a4,1(a5!)
1c00a1ee:	f9f70693          	addi	a3,a4,-97
1c00a1f2:	0ff6f693          	andi	a3,a3,255
1c00a1f6:	fe070613          	addi	a2,a4,-32
1c00a1fa:	00d56e63          	bltu	a0,a3,1c00a216 <pos_libc_prf+0x1072>
1c00a1fe:	fec78fa3          	sb	a2,-1(a5)
1c00a202:	0017c70b          	p.lbu	a4,1(a5!)
1c00a206:	f9f70693          	addi	a3,a4,-97
1c00a20a:	0ff6f693          	andi	a3,a3,255
1c00a20e:	fe070613          	addi	a2,a4,-32
1c00a212:	fed576e3          	bleu	a3,a0,1c00a1fe <pos_libc_prf+0x105a>
1c00a216:	fb71                	bnez	a4,1c00a1ea <pos_libc_prf+0x1046>
1c00a218:	d4eff06f          	j	1c009766 <pos_libc_prf+0x5c2>
1c00a21c:	4c92                	lw	s9,4(sp)
1c00a21e:	02410a13          	addi	s4,sp,36
1c00a222:	998ff06f          	j	1c0093ba <pos_libc_prf+0x216>
1c00a226:	4922                	lw	s2,8(sp)
1c00a228:	8dd2                	mv	s11,s4
1c00a22a:	a029                	j	1c00a234 <pos_libc_prf+0x1090>
1c00a22c:	9982                	jalr	s3
1c00a22e:	1dfd                	addi	s11,s11,-1
1c00a230:	8ff52563          	p.beqimm	a0,-1,1c00931a <pos_libc_prf+0x176>
1c00a234:	85de                	mv	a1,s7
1c00a236:	03000513          	li	a0,48
1c00a23a:	ffb049e3          	bgtz	s11,1c00a22c <pos_libc_prf+0x1088>
1c00a23e:	41490933          	sub	s2,s2,s4
1c00a242:	a62ff06f          	j	1c0094a4 <pos_libc_prf+0x300>
1c00a246:	4712                	lw	a4,4(sp)
1c00a248:	12070fe3          	beqz	a4,1c00ab86 <pos_libc_prf+0x19e2>
1c00a24c:	03000793          	li	a5,48
1c00a250:	02f10223          	sb	a5,36(sp)
1c00a254:	019467b3          	or	a5,s0,s9
1c00a258:	14078ae3          	beqz	a5,1c00abac <pos_libc_prf+0x1a08>
1c00a25c:	02510593          	addi	a1,sp,37
1c00a260:	4905                	li	s2,1
1c00a262:	86ae                	mv	a3,a1
1c00a264:	87b6                	mv	a5,a3
1c00a266:	a011                	j	1c00a26a <pos_libc_prf+0x10c6>
1c00a268:	87b2                	mv	a5,a2
1c00a26a:	01dc9613          	slli	a2,s9,0x1d
1c00a26e:	f8343733          	p.bclr	a4,s0,28,3
1c00a272:	800d                	srli	s0,s0,0x3
1c00a274:	8c51                	or	s0,s0,a2
1c00a276:	03070713          	addi	a4,a4,48
1c00a27a:	003cdc93          	srli	s9,s9,0x3
1c00a27e:	00e78023          	sb	a4,0(a5)
1c00a282:	01946733          	or	a4,s0,s9
1c00a286:	00178613          	addi	a2,a5,1
1c00a28a:	ff79                	bnez	a4,1c00a268 <pos_libc_prf+0x10c4>
1c00a28c:	00060023          	sb	zero,0(a2)
1c00a290:	8e0d                	sub	a2,a2,a1
1c00a292:	00f6fc63          	bleu	a5,a3,1c00a2aa <pos_libc_prf+0x1106>
1c00a296:	0006c583          	lbu	a1,0(a3)
1c00a29a:	0007c703          	lbu	a4,0(a5)
1c00a29e:	feb78fab          	p.sb	a1,-1(a5!)
1c00a2a2:	00e680ab          	p.sb	a4,1(a3!)
1c00a2a6:	fef6e8e3          	bltu	a3,a5,1c00a296 <pos_libc_prf+0x10f2>
1c00a2aa:	9932                	add	s2,s2,a2
1c00a2ac:	c202                	sw	zero,4(sp)
1c00a2ae:	97aff06f          	j	1c009428 <pos_libc_prf+0x284>
1c00a2b2:	111057e3          	blez	a7,1c00abc0 <pos_libc_prf+0x1a1c>
1c00a2b6:	00279e13          	slli	t3,a5,0x2
1c00a2ba:	01e7df13          	srli	t5,a5,0x1e
1c00a2be:	00269e93          	slli	t4,a3,0x2
1c00a2c2:	00fe05b3          	add	a1,t3,a5
1c00a2c6:	01df6eb3          	or	t4,t5,t4
1c00a2ca:	9eb6                	add	t4,t4,a3
1c00a2cc:	01c5b6b3          	sltu	a3,a1,t3
1c00a2d0:	96f6                	add	a3,a3,t4
1c00a2d2:	01f5d793          	srli	a5,a1,0x1f
1c00a2d6:	0686                	slli	a3,a3,0x1
1c00a2d8:	8edd                	or	a3,a3,a5
1c00a2da:	01c6d793          	srli	a5,a3,0x1c
1c00a2de:	03078793          	addi	a5,a5,48
1c00a2e2:	10000e37          	lui	t3,0x10000
1c00a2e6:	1e7d                	addi	t3,t3,-1
1c00a2e8:	00f30023          	sb	a5,0(t1)
1c00a2ec:	01c6f6b3          	and	a3,a3,t3
1c00a2f0:	00159793          	slli	a5,a1,0x1
1c00a2f4:	1618aee3          	p.beqimm	a7,1,1c00ac70 <pos_libc_prf+0x1acc>
1c00a2f8:	01e7df13          	srli	t5,a5,0x1e
1c00a2fc:	00269e93          	slli	t4,a3,0x2
1c00a300:	058e                	slli	a1,a1,0x3
1c00a302:	00f58533          	add	a0,a1,a5
1c00a306:	01df6eb3          	or	t4,t5,t4
1c00a30a:	9eb6                	add	t4,t4,a3
1c00a30c:	00b536b3          	sltu	a3,a0,a1
1c00a310:	96f6                	add	a3,a3,t4
1c00a312:	01f55793          	srli	a5,a0,0x1f
1c00a316:	0686                	slli	a3,a3,0x1
1c00a318:	8edd                	or	a3,a3,a5
1c00a31a:	01c6d793          	srli	a5,a3,0x1c
1c00a31e:	03078793          	addi	a5,a5,48
1c00a322:	00f300a3          	sb	a5,1(t1)
1c00a326:	01c6f6b3          	and	a3,a3,t3
1c00a32a:	00151793          	slli	a5,a0,0x1
1c00a32e:	1628a3e3          	p.beqimm	a7,2,1c00ac94 <pos_libc_prf+0x1af0>
1c00a332:	01e7df13          	srli	t5,a5,0x1e
1c00a336:	00269e93          	slli	t4,a3,0x2
1c00a33a:	050e                	slli	a0,a0,0x3
1c00a33c:	00f505b3          	add	a1,a0,a5
1c00a340:	01df6eb3          	or	t4,t5,t4
1c00a344:	9eb6                	add	t4,t4,a3
1c00a346:	00a5b6b3          	sltu	a3,a1,a0
1c00a34a:	96f6                	add	a3,a3,t4
1c00a34c:	01f5d793          	srli	a5,a1,0x1f
1c00a350:	0686                	slli	a3,a3,0x1
1c00a352:	8edd                	or	a3,a3,a5
1c00a354:	01c6d793          	srli	a5,a3,0x1c
1c00a358:	03078793          	addi	a5,a5,48
1c00a35c:	00f30123          	sb	a5,2(t1)
1c00a360:	ffd88a13          	addi	s4,a7,-3
1c00a364:	00159793          	slli	a5,a1,0x1
1c00a368:	01c6f6b3          	and	a3,a3,t3
1c00a36c:	134050e3          	blez	s4,1c00ac8c <pos_libc_prf+0x1ae8>
1c00a370:	01e7df13          	srli	t5,a5,0x1e
1c00a374:	00269e93          	slli	t4,a3,0x2
1c00a378:	058e                	slli	a1,a1,0x3
1c00a37a:	00f58533          	add	a0,a1,a5
1c00a37e:	01df6eb3          	or	t4,t5,t4
1c00a382:	9eb6                	add	t4,t4,a3
1c00a384:	00b536b3          	sltu	a3,a0,a1
1c00a388:	96f6                	add	a3,a3,t4
1c00a38a:	01f55793          	srli	a5,a0,0x1f
1c00a38e:	0686                	slli	a3,a3,0x1
1c00a390:	8edd                	or	a3,a3,a5
1c00a392:	01c6d793          	srli	a5,a3,0x1c
1c00a396:	03078793          	addi	a5,a5,48
1c00a39a:	00f301a3          	sb	a5,3(t1)
1c00a39e:	ffc88a13          	addi	s4,a7,-4
1c00a3a2:	00151793          	slli	a5,a0,0x1
1c00a3a6:	01c6f6b3          	and	a3,a3,t3
1c00a3aa:	134056e3          	blez	s4,1c00acd6 <pos_libc_prf+0x1b32>
1c00a3ae:	01e7df13          	srli	t5,a5,0x1e
1c00a3b2:	00269e93          	slli	t4,a3,0x2
1c00a3b6:	050e                	slli	a0,a0,0x3
1c00a3b8:	00f505b3          	add	a1,a0,a5
1c00a3bc:	01df6eb3          	or	t4,t5,t4
1c00a3c0:	9eb6                	add	t4,t4,a3
1c00a3c2:	00a5b6b3          	sltu	a3,a1,a0
1c00a3c6:	96f6                	add	a3,a3,t4
1c00a3c8:	01f5d793          	srli	a5,a1,0x1f
1c00a3cc:	0686                	slli	a3,a3,0x1
1c00a3ce:	8edd                	or	a3,a3,a5
1c00a3d0:	01c6d793          	srli	a5,a3,0x1c
1c00a3d4:	03078793          	addi	a5,a5,48
1c00a3d8:	00f30223          	sb	a5,4(t1)
1c00a3dc:	ffb88a13          	addi	s4,a7,-5
1c00a3e0:	00159793          	slli	a5,a1,0x1
1c00a3e4:	01c6f6b3          	and	a3,a3,t3
1c00a3e8:	0f4053e3          	blez	s4,1c00acce <pos_libc_prf+0x1b2a>
1c00a3ec:	01e7df13          	srli	t5,a5,0x1e
1c00a3f0:	00269e93          	slli	t4,a3,0x2
1c00a3f4:	058e                	slli	a1,a1,0x3
1c00a3f6:	00f58533          	add	a0,a1,a5
1c00a3fa:	01df6eb3          	or	t4,t5,t4
1c00a3fe:	9eb6                	add	t4,t4,a3
1c00a400:	00b536b3          	sltu	a3,a0,a1
1c00a404:	96f6                	add	a3,a3,t4
1c00a406:	01f55793          	srli	a5,a0,0x1f
1c00a40a:	0686                	slli	a3,a3,0x1
1c00a40c:	8edd                	or	a3,a3,a5
1c00a40e:	01c6d793          	srli	a5,a3,0x1c
1c00a412:	03078793          	addi	a5,a5,48
1c00a416:	00f302a3          	sb	a5,5(t1)
1c00a41a:	ffa88a13          	addi	s4,a7,-6
1c00a41e:	00151793          	slli	a5,a0,0x1
1c00a422:	01c6f6b3          	and	a3,a3,t3
1c00a426:	0b4050e3          	blez	s4,1c00acc6 <pos_libc_prf+0x1b22>
1c00a42a:	01e7df13          	srli	t5,a5,0x1e
1c00a42e:	00269e93          	slli	t4,a3,0x2
1c00a432:	050e                	slli	a0,a0,0x3
1c00a434:	00f505b3          	add	a1,a0,a5
1c00a438:	01df6eb3          	or	t4,t5,t4
1c00a43c:	9eb6                	add	t4,t4,a3
1c00a43e:	00a5b6b3          	sltu	a3,a1,a0
1c00a442:	96f6                	add	a3,a3,t4
1c00a444:	01f5d793          	srli	a5,a1,0x1f
1c00a448:	0686                	slli	a3,a3,0x1
1c00a44a:	8edd                	or	a3,a3,a5
1c00a44c:	01c6d793          	srli	a5,a3,0x1c
1c00a450:	03078793          	addi	a5,a5,48
1c00a454:	00f30323          	sb	a5,6(t1)
1c00a458:	ff988a13          	addi	s4,a7,-7
1c00a45c:	00159793          	slli	a5,a1,0x1
1c00a460:	01c6f6b3          	and	a3,a3,t3
1c00a464:	05405de3          	blez	s4,1c00acbe <pos_libc_prf+0x1b1a>
1c00a468:	058e                	slli	a1,a1,0x3
1c00a46a:	01e7de93          	srli	t4,a5,0x1e
1c00a46e:	00269513          	slli	a0,a3,0x2
1c00a472:	97ae                	add	a5,a5,a1
1c00a474:	00aee533          	or	a0,t4,a0
1c00a478:	9536                	add	a0,a0,a3
1c00a47a:	00b7b6b3          	sltu	a3,a5,a1
1c00a47e:	96aa                	add	a3,a3,a0
1c00a480:	01f7d593          	srli	a1,a5,0x1f
1c00a484:	0686                	slli	a3,a3,0x1
1c00a486:	8ecd                	or	a3,a3,a1
1c00a488:	01c6d593          	srli	a1,a3,0x1c
1c00a48c:	03058593          	addi	a1,a1,48
1c00a490:	0786                	slli	a5,a5,0x1
1c00a492:	00b303a3          	sb	a1,7(t1)
1c00a496:	ff888a13          	addi	s4,a7,-8
1c00a49a:	85be                	mv	a1,a5
1c00a49c:	01c6f6b3          	and	a3,a3,t3
1c00a4a0:	01405be3          	blez	s4,1c00acb6 <pos_libc_prf+0x1b12>
1c00a4a4:	078a                	slli	a5,a5,0x2
1c00a4a6:	01e5de13          	srli	t3,a1,0x1e
1c00a4aa:	00269513          	slli	a0,a3,0x2
1c00a4ae:	95be                	add	a1,a1,a5
1c00a4b0:	00ae6533          	or	a0,t3,a0
1c00a4b4:	9536                	add	a0,a0,a3
1c00a4b6:	00f5b6b3          	sltu	a3,a1,a5
1c00a4ba:	96aa                	add	a3,a3,a0
1c00a4bc:	01f5d793          	srli	a5,a1,0x1f
1c00a4c0:	0686                	slli	a3,a3,0x1
1c00a4c2:	8edd                	or	a3,a3,a5
1c00a4c4:	01c6d793          	srli	a5,a3,0x1c
1c00a4c8:	03078793          	addi	a5,a5,48
1c00a4cc:	10000e37          	lui	t3,0x10000
1c00a4d0:	1e7d                	addi	t3,t3,-1
1c00a4d2:	00f30423          	sb	a5,8(t1)
1c00a4d6:	ff788a13          	addi	s4,a7,-9
1c00a4da:	00159793          	slli	a5,a1,0x1
1c00a4de:	01c6f6b3          	and	a3,a3,t3
1c00a4e2:	7d405663          	blez	s4,1c00acae <pos_libc_prf+0x1b0a>
1c00a4e6:	01e7df13          	srli	t5,a5,0x1e
1c00a4ea:	00269e93          	slli	t4,a3,0x2
1c00a4ee:	058e                	slli	a1,a1,0x3
1c00a4f0:	00f58533          	add	a0,a1,a5
1c00a4f4:	01df6eb3          	or	t4,t5,t4
1c00a4f8:	9eb6                	add	t4,t4,a3
1c00a4fa:	00b536b3          	sltu	a3,a0,a1
1c00a4fe:	96f6                	add	a3,a3,t4
1c00a500:	01f55793          	srli	a5,a0,0x1f
1c00a504:	0686                	slli	a3,a3,0x1
1c00a506:	8edd                	or	a3,a3,a5
1c00a508:	01c6d793          	srli	a5,a3,0x1c
1c00a50c:	03078793          	addi	a5,a5,48
1c00a510:	00f304a3          	sb	a5,9(t1)
1c00a514:	ff688a13          	addi	s4,a7,-10
1c00a518:	00151793          	slli	a5,a0,0x1
1c00a51c:	01c6f6b3          	and	a3,a3,t3
1c00a520:	79405363          	blez	s4,1c00aca6 <pos_libc_prf+0x1b02>
1c00a524:	01e7df13          	srli	t5,a5,0x1e
1c00a528:	00269e93          	slli	t4,a3,0x2
1c00a52c:	050e                	slli	a0,a0,0x3
1c00a52e:	00f505b3          	add	a1,a0,a5
1c00a532:	01df6eb3          	or	t4,t5,t4
1c00a536:	9eb6                	add	t4,t4,a3
1c00a538:	00a5b6b3          	sltu	a3,a1,a0
1c00a53c:	96f6                	add	a3,a3,t4
1c00a53e:	01f5d793          	srli	a5,a1,0x1f
1c00a542:	0686                	slli	a3,a3,0x1
1c00a544:	8edd                	or	a3,a3,a5
1c00a546:	01c6d793          	srli	a5,a3,0x1c
1c00a54a:	03078793          	addi	a5,a5,48
1c00a54e:	00f30523          	sb	a5,10(t1)
1c00a552:	ff588a13          	addi	s4,a7,-11
1c00a556:	00159793          	slli	a5,a1,0x1
1c00a55a:	01c6f6b3          	and	a3,a3,t3
1c00a55e:	75405063          	blez	s4,1c00ac9e <pos_libc_prf+0x1afa>
1c00a562:	01e7df13          	srli	t5,a5,0x1e
1c00a566:	00269e93          	slli	t4,a3,0x2
1c00a56a:	058e                	slli	a1,a1,0x3
1c00a56c:	00f58533          	add	a0,a1,a5
1c00a570:	01df6eb3          	or	t4,t5,t4
1c00a574:	9eb6                	add	t4,t4,a3
1c00a576:	00b536b3          	sltu	a3,a0,a1
1c00a57a:	96f6                	add	a3,a3,t4
1c00a57c:	01f55793          	srli	a5,a0,0x1f
1c00a580:	0686                	slli	a3,a3,0x1
1c00a582:	8edd                	or	a3,a3,a5
1c00a584:	01c6d793          	srli	a5,a3,0x1c
1c00a588:	03078793          	addi	a5,a5,48
1c00a58c:	00f305a3          	sb	a5,11(t1)
1c00a590:	ff488a13          	addi	s4,a7,-12
1c00a594:	00151793          	slli	a5,a0,0x1
1c00a598:	01c6f6b3          	and	a3,a3,t3
1c00a59c:	6f405163          	blez	s4,1c00ac7e <pos_libc_prf+0x1ada>
1c00a5a0:	050e                	slli	a0,a0,0x3
1c00a5a2:	01e7de93          	srli	t4,a5,0x1e
1c00a5a6:	00269813          	slli	a6,a3,0x2
1c00a5aa:	00f505b3          	add	a1,a0,a5
1c00a5ae:	010ee833          	or	a6,t4,a6
1c00a5b2:	9836                	add	a6,a6,a3
1c00a5b4:	00a5b6b3          	sltu	a3,a1,a0
1c00a5b8:	96c2                	add	a3,a3,a6
1c00a5ba:	01f5d793          	srli	a5,a1,0x1f
1c00a5be:	0686                	slli	a3,a3,0x1
1c00a5c0:	8edd                	or	a3,a3,a5
1c00a5c2:	01c6d793          	srli	a5,a3,0x1c
1c00a5c6:	03078793          	addi	a5,a5,48
1c00a5ca:	00f30623          	sb	a5,12(t1)
1c00a5ce:	ff388a13          	addi	s4,a7,-13
1c00a5d2:	00159793          	slli	a5,a1,0x1
1c00a5d6:	01c6f6b3          	and	a3,a3,t3
1c00a5da:	00d30513          	addi	a0,t1,13
1c00a5de:	480d                	li	a6,3
1c00a5e0:	0d405163          	blez	s4,1c00a6a2 <pos_libc_prf+0x14fe>
1c00a5e4:	01e7de93          	srli	t4,a5,0x1e
1c00a5e8:	00269813          	slli	a6,a3,0x2
1c00a5ec:	058e                	slli	a1,a1,0x3
1c00a5ee:	00f58533          	add	a0,a1,a5
1c00a5f2:	010ee833          	or	a6,t4,a6
1c00a5f6:	9836                	add	a6,a6,a3
1c00a5f8:	00b536b3          	sltu	a3,a0,a1
1c00a5fc:	96c2                	add	a3,a3,a6
1c00a5fe:	01f55793          	srli	a5,a0,0x1f
1c00a602:	0686                	slli	a3,a3,0x1
1c00a604:	8edd                	or	a3,a3,a5
1c00a606:	01c6d793          	srli	a5,a3,0x1c
1c00a60a:	03078793          	addi	a5,a5,48
1c00a60e:	00f306a3          	sb	a5,13(t1)
1c00a612:	ff288a13          	addi	s4,a7,-14
1c00a616:	00151793          	slli	a5,a0,0x1
1c00a61a:	01c6f6b3          	and	a3,a3,t3
1c00a61e:	65405c63          	blez	s4,1c00ac76 <pos_libc_prf+0x1ad2>
1c00a622:	050e                	slli	a0,a0,0x3
1c00a624:	01e7de93          	srli	t4,a5,0x1e
1c00a628:	00269813          	slli	a6,a3,0x2
1c00a62c:	00f505b3          	add	a1,a0,a5
1c00a630:	010ee833          	or	a6,t4,a6
1c00a634:	9836                	add	a6,a6,a3
1c00a636:	00a5b6b3          	sltu	a3,a1,a0
1c00a63a:	96c2                	add	a3,a3,a6
1c00a63c:	01f5d793          	srli	a5,a1,0x1f
1c00a640:	0686                	slli	a3,a3,0x1
1c00a642:	8edd                	or	a3,a3,a5
1c00a644:	01c6d793          	srli	a5,a3,0x1c
1c00a648:	03078793          	addi	a5,a5,48
1c00a64c:	00f30723          	sb	a5,14(t1)
1c00a650:	ff188a13          	addi	s4,a7,-15
1c00a654:	00159793          	slli	a5,a1,0x1
1c00a658:	01c6f6b3          	and	a3,a3,t3
1c00a65c:	00f30513          	addi	a0,t1,15
1c00a660:	4805                	li	a6,1
1c00a662:	05405063          	blez	s4,1c00a6a2 <pos_libc_prf+0x14fe>
1c00a666:	01e7d813          	srli	a6,a5,0x1e
1c00a66a:	058e                	slli	a1,a1,0x3
1c00a66c:	00269513          	slli	a0,a3,0x2
1c00a670:	97ae                	add	a5,a5,a1
1c00a672:	00a86533          	or	a0,a6,a0
1c00a676:	9536                	add	a0,a0,a3
1c00a678:	00b7b6b3          	sltu	a3,a5,a1
1c00a67c:	96aa                	add	a3,a3,a0
1c00a67e:	01f7d593          	srli	a1,a5,0x1f
1c00a682:	0686                	slli	a3,a3,0x1
1c00a684:	8ecd                	or	a3,a3,a1
1c00a686:	01c6d593          	srli	a1,a3,0x1c
1c00a68a:	03058593          	addi	a1,a1,48
1c00a68e:	01030513          	addi	a0,t1,16
1c00a692:	0786                	slli	a5,a5,0x1
1c00a694:	01c6f6b3          	and	a3,a3,t3
1c00a698:	00b307a3          	sb	a1,15(t1)
1c00a69c:	ff088a13          	addi	s4,a7,-16
1c00a6a0:	4801                	li	a6,0
1c00a6a2:	4712                	lw	a4,4(sp)
1c00a6a4:	4e070663          	beqz	a4,1c00ab90 <pos_libc_prf+0x19ec>
1c00a6a8:	02e00893          	li	a7,46
1c00a6ac:	01150023          	sb	a7,0(a0)
1c00a6b0:	8326                	mv	t1,s1
1c00a6b2:	cc02                	sw	zero,24(sp)
1c00a6b4:	00150593          	addi	a1,a0,1
1c00a6b8:	4881                	li	a7,0
1c00a6ba:	62605263          	blez	t1,1c00acde <pos_libc_prf+0x1b3a>
1c00a6be:	62080063          	beqz	a6,1c00acde <pos_libc_prf+0x1b3a>
1c00a6c2:	00279513          	slli	a0,a5,0x2
1c00a6c6:	01e7de93          	srli	t4,a5,0x1e
1c00a6ca:	00269e13          	slli	t3,a3,0x2
1c00a6ce:	97aa                	add	a5,a5,a0
1c00a6d0:	01ceee33          	or	t3,t4,t3
1c00a6d4:	96f2                	add	a3,a3,t3
1c00a6d6:	00a7beb3          	sltu	t4,a5,a0
1c00a6da:	9eb6                	add	t4,t4,a3
1c00a6dc:	0e86                	slli	t4,t4,0x1
1c00a6de:	01f7d693          	srli	a3,a5,0x1f
1c00a6e2:	01d6eeb3          	or	t4,a3,t4
1c00a6e6:	01ced693          	srli	a3,t4,0x1c
1c00a6ea:	03068693          	addi	a3,a3,48
1c00a6ee:	00d58023          	sb	a3,0(a1)
1c00a6f2:	fff30493          	addi	s1,t1,-1
1c00a6f6:	00158513          	addi	a0,a1,1
1c00a6fa:	00179693          	slli	a3,a5,0x1
1c00a6fe:	42048263          	beqz	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a702:	42182063          	p.beqimm	a6,1,1c00ab22 <pos_libc_prf+0x197e>
1c00a706:	10000e37          	lui	t3,0x10000
1c00a70a:	1e7d                	addi	t3,t3,-1
1c00a70c:	01cefeb3          	and	t4,t4,t3
1c00a710:	078e                	slli	a5,a5,0x3
1c00a712:	01e6df13          	srli	t5,a3,0x1e
1c00a716:	002e9513          	slli	a0,t4,0x2
1c00a71a:	96be                	add	a3,a3,a5
1c00a71c:	00af6533          	or	a0,t5,a0
1c00a720:	9eaa                	add	t4,t4,a0
1c00a722:	00f6b7b3          	sltu	a5,a3,a5
1c00a726:	97f6                	add	a5,a5,t4
1c00a728:	01f6d513          	srli	a0,a3,0x1f
1c00a72c:	0786                	slli	a5,a5,0x1
1c00a72e:	8fc9                	or	a5,a5,a0
1c00a730:	01c7d513          	srli	a0,a5,0x1c
1c00a734:	03050513          	addi	a0,a0,48
1c00a738:	00a580a3          	sb	a0,1(a1)
1c00a73c:	ffe30493          	addi	s1,t1,-2
1c00a740:	00258513          	addi	a0,a1,2
1c00a744:	00169e93          	slli	t4,a3,0x1
1c00a748:	01c7f7b3          	and	a5,a5,t3
1c00a74c:	3c048b63          	beqz	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a750:	3c282963          	p.beqimm	a6,2,1c00ab22 <pos_libc_prf+0x197e>
1c00a754:	01eedf13          	srli	t5,t4,0x1e
1c00a758:	068e                	slli	a3,a3,0x3
1c00a75a:	00279513          	slli	a0,a5,0x2
1c00a75e:	9eb6                	add	t4,t4,a3
1c00a760:	00af6533          	or	a0,t5,a0
1c00a764:	00deb6b3          	sltu	a3,t4,a3
1c00a768:	97aa                	add	a5,a5,a0
1c00a76a:	97b6                	add	a5,a5,a3
1c00a76c:	0786                	slli	a5,a5,0x1
1c00a76e:	01fed693          	srli	a3,t4,0x1f
1c00a772:	8fd5                	or	a5,a5,a3
1c00a774:	01c7d693          	srli	a3,a5,0x1c
1c00a778:	03068693          	addi	a3,a3,48
1c00a77c:	00d58123          	sb	a3,2(a1)
1c00a780:	ffd30493          	addi	s1,t1,-3
1c00a784:	00358513          	addi	a0,a1,3
1c00a788:	001e9693          	slli	a3,t4,0x1
1c00a78c:	01c7ff33          	and	t5,a5,t3
1c00a790:	38905963          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a794:	38382763          	p.beqimm	a6,3,1c00ab22 <pos_libc_prf+0x197e>
1c00a798:	003e9513          	slli	a0,t4,0x3
1c00a79c:	01e6d793          	srli	a5,a3,0x1e
1c00a7a0:	002f1e93          	slli	t4,t5,0x2
1c00a7a4:	96aa                	add	a3,a3,a0
1c00a7a6:	01d7eeb3          	or	t4,a5,t4
1c00a7aa:	9efa                	add	t4,t4,t5
1c00a7ac:	00a6b7b3          	sltu	a5,a3,a0
1c00a7b0:	97f6                	add	a5,a5,t4
1c00a7b2:	01f6d513          	srli	a0,a3,0x1f
1c00a7b6:	0786                	slli	a5,a5,0x1
1c00a7b8:	8fc9                	or	a5,a5,a0
1c00a7ba:	01c7d513          	srli	a0,a5,0x1c
1c00a7be:	03050513          	addi	a0,a0,48
1c00a7c2:	00a581a3          	sb	a0,3(a1)
1c00a7c6:	ffc30493          	addi	s1,t1,-4
1c00a7ca:	00458513          	addi	a0,a1,4
1c00a7ce:	00169e93          	slli	t4,a3,0x1
1c00a7d2:	01c7fe33          	and	t3,a5,t3
1c00a7d6:	34905663          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a7da:	34482463          	p.beqimm	a6,4,1c00ab22 <pos_libc_prf+0x197e>
1c00a7de:	068e                	slli	a3,a3,0x3
1c00a7e0:	01eed793          	srli	a5,t4,0x1e
1c00a7e4:	002e1513          	slli	a0,t3,0x2
1c00a7e8:	9eb6                	add	t4,t4,a3
1c00a7ea:	8d5d                	or	a0,a0,a5
1c00a7ec:	9e2a                	add	t3,t3,a0
1c00a7ee:	00deb7b3          	sltu	a5,t4,a3
1c00a7f2:	97f2                	add	a5,a5,t3
1c00a7f4:	01fed693          	srli	a3,t4,0x1f
1c00a7f8:	0786                	slli	a5,a5,0x1
1c00a7fa:	8fd5                	or	a5,a5,a3
1c00a7fc:	01c7d693          	srli	a3,a5,0x1c
1c00a800:	03068693          	addi	a3,a3,48
1c00a804:	00d58223          	sb	a3,4(a1)
1c00a808:	ffb30493          	addi	s1,t1,-5
1c00a80c:	00558513          	addi	a0,a1,5
1c00a810:	001e9693          	slli	a3,t4,0x1
1c00a814:	30905763          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a818:	30582563          	p.beqimm	a6,5,1c00ab22 <pos_libc_prf+0x197e>
1c00a81c:	10000e37          	lui	t3,0x10000
1c00a820:	1e7d                	addi	t3,t3,-1
1c00a822:	01c7f7b3          	and	a5,a5,t3
1c00a826:	01e6de93          	srli	t4,a3,0x1e
1c00a82a:	00269513          	slli	a0,a3,0x2
1c00a82e:	00279f13          	slli	t5,a5,0x2
1c00a832:	96aa                	add	a3,a3,a0
1c00a834:	01eeef33          	or	t5,t4,t5
1c00a838:	00a6b533          	sltu	a0,a3,a0
1c00a83c:	97fa                	add	a5,a5,t5
1c00a83e:	97aa                	add	a5,a5,a0
1c00a840:	00179e93          	slli	t4,a5,0x1
1c00a844:	01f6d513          	srli	a0,a3,0x1f
1c00a848:	01d56eb3          	or	t4,a0,t4
1c00a84c:	01ced793          	srli	a5,t4,0x1c
1c00a850:	03078793          	addi	a5,a5,48
1c00a854:	00f582a3          	sb	a5,5(a1)
1c00a858:	ffa30493          	addi	s1,t1,-6
1c00a85c:	00658513          	addi	a0,a1,6
1c00a860:	00169793          	slli	a5,a3,0x1
1c00a864:	01cefeb3          	and	t4,t4,t3
1c00a868:	2a905d63          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a86c:	2a682b63          	p.beqimm	a6,6,1c00ab22 <pos_libc_prf+0x197e>
1c00a870:	068e                	slli	a3,a3,0x3
1c00a872:	01e7df13          	srli	t5,a5,0x1e
1c00a876:	002e9513          	slli	a0,t4,0x2
1c00a87a:	97b6                	add	a5,a5,a3
1c00a87c:	00af6533          	or	a0,t5,a0
1c00a880:	9eaa                	add	t4,t4,a0
1c00a882:	00d7b6b3          	sltu	a3,a5,a3
1c00a886:	96f6                	add	a3,a3,t4
1c00a888:	01f7d513          	srli	a0,a5,0x1f
1c00a88c:	00169e93          	slli	t4,a3,0x1
1c00a890:	01d56eb3          	or	t4,a0,t4
1c00a894:	01ced693          	srli	a3,t4,0x1c
1c00a898:	03068693          	addi	a3,a3,48
1c00a89c:	00d58323          	sb	a3,6(a1)
1c00a8a0:	ff930493          	addi	s1,t1,-7
1c00a8a4:	00758513          	addi	a0,a1,7
1c00a8a8:	00179693          	slli	a3,a5,0x1
1c00a8ac:	01cefeb3          	and	t4,t4,t3
1c00a8b0:	26905963          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a8b4:	26782763          	p.beqimm	a6,7,1c00ab22 <pos_libc_prf+0x197e>
1c00a8b8:	078e                	slli	a5,a5,0x3
1c00a8ba:	01e6df13          	srli	t5,a3,0x1e
1c00a8be:	002e9513          	slli	a0,t4,0x2
1c00a8c2:	96be                	add	a3,a3,a5
1c00a8c4:	00af6533          	or	a0,t5,a0
1c00a8c8:	9eaa                	add	t4,t4,a0
1c00a8ca:	00f6b7b3          	sltu	a5,a3,a5
1c00a8ce:	97f6                	add	a5,a5,t4
1c00a8d0:	01f6d513          	srli	a0,a3,0x1f
1c00a8d4:	00179e93          	slli	t4,a5,0x1
1c00a8d8:	01d56eb3          	or	t4,a0,t4
1c00a8dc:	01ced793          	srli	a5,t4,0x1c
1c00a8e0:	03078793          	addi	a5,a5,48
1c00a8e4:	00f583a3          	sb	a5,7(a1)
1c00a8e8:	ff830493          	addi	s1,t1,-8
1c00a8ec:	00858513          	addi	a0,a1,8
1c00a8f0:	00169793          	slli	a5,a3,0x1
1c00a8f4:	01cefeb3          	and	t4,t4,t3
1c00a8f8:	22905563          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a8fc:	22882363          	p.beqimm	a6,8,1c00ab22 <pos_libc_prf+0x197e>
1c00a900:	01e7df13          	srli	t5,a5,0x1e
1c00a904:	068e                	slli	a3,a3,0x3
1c00a906:	002e9513          	slli	a0,t4,0x2
1c00a90a:	97b6                	add	a5,a5,a3
1c00a90c:	00af6533          	or	a0,t5,a0
1c00a910:	9eaa                	add	t4,t4,a0
1c00a912:	00d7b6b3          	sltu	a3,a5,a3
1c00a916:	96f6                	add	a3,a3,t4
1c00a918:	01f7d513          	srli	a0,a5,0x1f
1c00a91c:	0686                	slli	a3,a3,0x1
1c00a91e:	8ec9                	or	a3,a3,a0
1c00a920:	01c6d513          	srli	a0,a3,0x1c
1c00a924:	03050513          	addi	a0,a0,48
1c00a928:	00a58423          	sb	a0,8(a1)
1c00a92c:	ff730493          	addi	s1,t1,-9
1c00a930:	00958513          	addi	a0,a1,9
1c00a934:	00179f13          	slli	t5,a5,0x1
1c00a938:	01c6feb3          	and	t4,a3,t3
1c00a93c:	1e905363          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a940:	1e982163          	p.beqimm	a6,9,1c00ab22 <pos_libc_prf+0x197e>
1c00a944:	078e                	slli	a5,a5,0x3
1c00a946:	01ef5293          	srli	t0,t5,0x1e
1c00a94a:	002e9513          	slli	a0,t4,0x2
1c00a94e:	01e786b3          	add	a3,a5,t5
1c00a952:	00a2e533          	or	a0,t0,a0
1c00a956:	00f6b7b3          	sltu	a5,a3,a5
1c00a95a:	9576                	add	a0,a0,t4
1c00a95c:	97aa                	add	a5,a5,a0
1c00a95e:	0786                	slli	a5,a5,0x1
1c00a960:	01f6d513          	srli	a0,a3,0x1f
1c00a964:	8fc9                	or	a5,a5,a0
1c00a966:	01c7d513          	srli	a0,a5,0x1c
1c00a96a:	03050513          	addi	a0,a0,48
1c00a96e:	00a584a3          	sb	a0,9(a1)
1c00a972:	ff630493          	addi	s1,t1,-10
1c00a976:	00a58513          	addi	a0,a1,10
1c00a97a:	0686                	slli	a3,a3,0x1
1c00a97c:	01c7f7b3          	and	a5,a5,t3
1c00a980:	1a905163          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a984:	18a82f63          	p.beqimm	a6,10,1c00ab22 <pos_libc_prf+0x197e>
1c00a988:	01e6de93          	srli	t4,a3,0x1e
1c00a98c:	00269513          	slli	a0,a3,0x2
1c00a990:	00279e13          	slli	t3,a5,0x2
1c00a994:	96aa                	add	a3,a3,a0
1c00a996:	01ceee33          	or	t3,t4,t3
1c00a99a:	00a6b533          	sltu	a0,a3,a0
1c00a99e:	97f2                	add	a5,a5,t3
1c00a9a0:	97aa                	add	a5,a5,a0
1c00a9a2:	00179e93          	slli	t4,a5,0x1
1c00a9a6:	01f6d513          	srli	a0,a3,0x1f
1c00a9aa:	01d56eb3          	or	t4,a0,t4
1c00a9ae:	01ced793          	srli	a5,t4,0x1c
1c00a9b2:	03078793          	addi	a5,a5,48
1c00a9b6:	10000e37          	lui	t3,0x10000
1c00a9ba:	1e7d                	addi	t3,t3,-1
1c00a9bc:	00f58523          	sb	a5,10(a1)
1c00a9c0:	ff530493          	addi	s1,t1,-11
1c00a9c4:	00b58513          	addi	a0,a1,11
1c00a9c8:	00169793          	slli	a5,a3,0x1
1c00a9cc:	01cefeb3          	and	t4,t4,t3
1c00a9d0:	14905963          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00a9d4:	14b82763          	p.beqimm	a6,11,1c00ab22 <pos_libc_prf+0x197e>
1c00a9d8:	068e                	slli	a3,a3,0x3
1c00a9da:	01e7df13          	srli	t5,a5,0x1e
1c00a9de:	002e9513          	slli	a0,t4,0x2
1c00a9e2:	97b6                	add	a5,a5,a3
1c00a9e4:	00af6533          	or	a0,t5,a0
1c00a9e8:	9eaa                	add	t4,t4,a0
1c00a9ea:	00d7b6b3          	sltu	a3,a5,a3
1c00a9ee:	96f6                	add	a3,a3,t4
1c00a9f0:	01f7d513          	srli	a0,a5,0x1f
1c00a9f4:	0686                	slli	a3,a3,0x1
1c00a9f6:	8ec9                	or	a3,a3,a0
1c00a9f8:	01c6d513          	srli	a0,a3,0x1c
1c00a9fc:	03050513          	addi	a0,a0,48
1c00aa00:	00a585a3          	sb	a0,11(a1)
1c00aa04:	ff430493          	addi	s1,t1,-12
1c00aa08:	00c58513          	addi	a0,a1,12
1c00aa0c:	00179e93          	slli	t4,a5,0x1
1c00aa10:	10905963          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00aa14:	10c82763          	p.beqimm	a6,12,1c00ab22 <pos_libc_prf+0x197e>
1c00aa18:	01c6f6b3          	and	a3,a3,t3
1c00aa1c:	01eedf13          	srli	t5,t4,0x1e
1c00aa20:	078e                	slli	a5,a5,0x3
1c00aa22:	00269513          	slli	a0,a3,0x2
1c00aa26:	9ebe                	add	t4,t4,a5
1c00aa28:	00af6533          	or	a0,t5,a0
1c00aa2c:	96aa                	add	a3,a3,a0
1c00aa2e:	00feb7b3          	sltu	a5,t4,a5
1c00aa32:	97b6                	add	a5,a5,a3
1c00aa34:	01fed513          	srli	a0,t4,0x1f
1c00aa38:	00179693          	slli	a3,a5,0x1
1c00aa3c:	8ec9                	or	a3,a3,a0
1c00aa3e:	01c6d793          	srli	a5,a3,0x1c
1c00aa42:	03078793          	addi	a5,a5,48
1c00aa46:	00f58623          	sb	a5,12(a1)
1c00aa4a:	ff330493          	addi	s1,t1,-13
1c00aa4e:	00d58513          	addi	a0,a1,13
1c00aa52:	001e9793          	slli	a5,t4,0x1
1c00aa56:	01c6ff33          	and	t5,a3,t3
1c00aa5a:	0c905463          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00aa5e:	0cd82263          	p.beqimm	a6,13,1c00ab22 <pos_libc_prf+0x197e>
1c00aa62:	003e9693          	slli	a3,t4,0x3
1c00aa66:	002f1513          	slli	a0,t5,0x2
1c00aa6a:	01e7de93          	srli	t4,a5,0x1e
1c00aa6e:	00aee533          	or	a0,t4,a0
1c00aa72:	97b6                	add	a5,a5,a3
1c00aa74:	957a                	add	a0,a0,t5
1c00aa76:	00d7b6b3          	sltu	a3,a5,a3
1c00aa7a:	96aa                	add	a3,a3,a0
1c00aa7c:	0686                	slli	a3,a3,0x1
1c00aa7e:	01f7d513          	srli	a0,a5,0x1f
1c00aa82:	8ec9                	or	a3,a3,a0
1c00aa84:	01c6d513          	srli	a0,a3,0x1c
1c00aa88:	03050513          	addi	a0,a0,48
1c00aa8c:	00a586a3          	sb	a0,13(a1)
1c00aa90:	ff230493          	addi	s1,t1,-14
1c00aa94:	00e58513          	addi	a0,a1,14
1c00aa98:	00179f13          	slli	t5,a5,0x1
1c00aa9c:	01c6feb3          	and	t4,a3,t3
1c00aaa0:	08905163          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00aaa4:	06e82f63          	p.beqimm	a6,14,1c00ab22 <pos_libc_prf+0x197e>
1c00aaa8:	078e                	slli	a5,a5,0x3
1c00aaaa:	002e9513          	slli	a0,t4,0x2
1c00aaae:	01ef5293          	srli	t0,t5,0x1e
1c00aab2:	01e786b3          	add	a3,a5,t5
1c00aab6:	00a2e533          	or	a0,t0,a0
1c00aaba:	9576                	add	a0,a0,t4
1c00aabc:	00f6b7b3          	sltu	a5,a3,a5
1c00aac0:	97aa                	add	a5,a5,a0
1c00aac2:	00179e93          	slli	t4,a5,0x1
1c00aac6:	01f6d513          	srli	a0,a3,0x1f
1c00aaca:	01d56eb3          	or	t4,a0,t4
1c00aace:	01ced793          	srli	a5,t4,0x1c
1c00aad2:	03078793          	addi	a5,a5,48
1c00aad6:	00f58723          	sb	a5,14(a1)
1c00aada:	ff130493          	addi	s1,t1,-15
1c00aade:	00f58513          	addi	a0,a1,15
1c00aae2:	00169793          	slli	a5,a3,0x1
1c00aae6:	01cefe33          	and	t3,t4,t3
1c00aaea:	02905c63          	blez	s1,1c00ab22 <pos_libc_prf+0x197e>
1c00aaee:	46c1                	li	a3,16
1c00aaf0:	02d81963          	bne	a6,a3,1c00ab22 <pos_libc_prf+0x197e>
1c00aaf4:	00279513          	slli	a0,a5,0x2
1c00aaf8:	01e7d813          	srli	a6,a5,0x1e
1c00aafc:	002e1693          	slli	a3,t3,0x2
1c00ab00:	97aa                	add	a5,a5,a0
1c00ab02:	00d866b3          	or	a3,a6,a3
1c00ab06:	00a7b7b3          	sltu	a5,a5,a0
1c00ab0a:	9e36                	add	t3,t3,a3
1c00ab0c:	97f2                	add	a5,a5,t3
1c00ab0e:	0786                	slli	a5,a5,0x1
1c00ab10:	83f1                	srli	a5,a5,0x1c
1c00ab12:	03078793          	addi	a5,a5,48
1c00ab16:	01058513          	addi	a0,a1,16
1c00ab1a:	00f587a3          	sb	a5,15(a1)
1c00ab1e:	ff030493          	addi	s1,t1,-16
1c00ab22:	47e2                	lw	a5,24(sp)
1c00ab24:	014785b3          	add	a1,a5,s4
1c00ab28:	9c0f9b63          	bnez	t6,1c009cfe <pos_libc_prf+0xb5a>
1c00ab2c:	95a6                	add	a1,a1,s1
1c00ab2e:	8ca6                	mv	s9,s1
1c00ab30:	9faff06f          	j	1c009d2a <pos_libc_prf+0xb86>
1c00ab34:	02d00793          	li	a5,45
1c00ab38:	411008b3          	neg	a7,a7
1c00ab3c:	00f500a3          	sb	a5,1(a0)
1c00ab40:	db4ff06f          	j	1c00a0f4 <pos_libc_prf+0xf50>
1c00ab44:	41fad793          	srai	a5,s5,0x1f
1c00ab48:	0156a023          	sw	s5,0(a3)
1c00ab4c:	c2dc                	sw	a5,4(a3)
1c00ab4e:	e94fe06f          	j	1c0091e2 <pos_libc_prf+0x3e>
1c00ab52:	4a62                	lw	s4,24(sp)
1c00ab54:	a039                	j	1c00ab62 <pos_libc_prf+0x19be>
1c00ab56:	9982                	jalr	s3
1c00ab58:	1a7d                	addi	s4,s4,-1
1c00ab5a:	01f53463          	p.bneimm	a0,-1,1c00ab62 <pos_libc_prf+0x19be>
1c00ab5e:	fbcfe06f          	j	1c00931a <pos_libc_prf+0x176>
1c00ab62:	85de                	mv	a1,s7
1c00ab64:	03000513          	li	a0,48
1c00ab68:	ff4047e3          	bgtz	s4,1c00ab56 <pos_libc_prf+0x19b2>
1c00ab6c:	4762                	lw	a4,24(sp)
1c00ab6e:	40e90933          	sub	s2,s2,a4
1c00ab72:	939fe06f          	j	1c0094aa <pos_libc_prf+0x306>
1c00ab76:	4741                	li	a4,16
1c00ab78:	04e4cf33          	p.min	t5,s1,a4
1c00ab7c:	1f7d                	addi	t5,t5,-1
1c00ab7e:	84b6                	mv	s1,a3
1c00ab80:	4f81                	li	t6,0
1c00ab82:	c67fe06f          	j	1c0097e8 <pos_libc_prf+0x644>
1c00ab86:	104c                	addi	a1,sp,36
1c00ab88:	4901                	li	s2,0
1c00ab8a:	86ae                	mv	a3,a1
1c00ab8c:	ed8ff06f          	j	1c00a264 <pos_libc_prf+0x10c0>
1c00ab90:	0c904463          	bgtz	s1,1c00ac58 <pos_libc_prf+0x1ab4>
1c00ab94:	4881                	li	a7,0
1c00ab96:	cc02                	sw	zero,24(sp)
1c00ab98:	b769                	j	1c00ab22 <pos_libc_prf+0x197e>
1c00ab9a:	4712                	lw	a4,4(sp)
1c00ab9c:	4f81                	li	t6,0
1c00ab9e:	e319                	bnez	a4,1c00aba4 <pos_libc_prf+0x1a00>
1c00aba0:	c3dfe06f          	j	1c0097dc <pos_libc_prf+0x638>
1c00aba4:	4f01                	li	t5,0
1c00aba6:	4f81                	li	t6,0
1c00aba8:	c41fe06f          	j	1c0097e8 <pos_libc_prf+0x644>
1c00abac:	020102a3          	sb	zero,37(sp)
1c00abb0:	c202                	sw	zero,4(sp)
1c00abb2:	4905                	li	s2,1
1c00abb4:	875fe06f          	j	1c009428 <pos_libc_prf+0x284>
1c00abb8:	06600d93          	li	s11,102
1c00abbc:	d1cff06f          	j	1c00a0d8 <pos_libc_prf+0xf34>
1c00abc0:	03000593          	li	a1,48
1c00abc4:	4712                	lw	a4,4(sp)
1c00abc6:	00b30023          	sb	a1,0(t1)
1c00abca:	e335                	bnez	a4,1c00ac2e <pos_libc_prf+0x1a8a>
1c00abcc:	06905b63          	blez	s1,1c00ac42 <pos_libc_prf+0x1a9e>
1c00abd0:	02e00593          	li	a1,46
1c00abd4:	00b300a3          	sb	a1,1(t1)
1c00abd8:	00230513          	addi	a0,t1,2
1c00abdc:	4841                	li	a6,16
1c00abde:	08088363          	beqz	a7,1c00ac64 <pos_libc_prf+0x1ac0>
1c00abe2:	41100733          	neg	a4,a7
1c00abe6:	04974733          	p.min	a4,a4,s1
1c00abea:	cc3a                	sw	a4,24(sp)
1c00abec:	40e48333          	sub	t1,s1,a4
1c00abf0:	85aa                	mv	a1,a0
1c00abf2:	4a01                	li	s4,0
1c00abf4:	4841                	li	a6,16
1c00abf6:	ac6044e3          	bgtz	t1,1c00a6be <pos_libc_prf+0x151a>
1c00abfa:	a0d5                	j	1c00acde <pos_libc_prf+0x1b3a>
1c00abfc:	4a72                	lw	s4,28(sp)
1c00abfe:	de4fe06f          	j	1c0091e2 <pos_libc_prf+0x3e>
1c00ac02:	6799                	lui	a5,0x6
1c00ac04:	16e78793          	addi	a5,a5,366 # 616e <pos_soc_event_callback+0x5d26>
1c00ac08:	00f31023          	sh	a5,0(t1)
1c00ac0c:	06e00793          	li	a5,110
1c00ac10:	00f30123          	sb	a5,2(t1)
1c00ac14:	c38ff06f          	j	1c00a04c <pos_libc_prf+0xea8>
1c00ac18:	679d                	lui	a5,0x7
1c00ac1a:	e6978793          	addi	a5,a5,-407 # 6e69 <pos_soc_event_callback+0x6a21>
1c00ac1e:	00f31023          	sh	a5,0(t1)
1c00ac22:	06600793          	li	a5,102
1c00ac26:	00f30123          	sb	a5,2(t1)
1c00ac2a:	c22ff06f          	j	1c00a04c <pos_libc_prf+0xea8>
1c00ac2e:	02e00593          	li	a1,46
1c00ac32:	00b300a3          	sb	a1,1(t1)
1c00ac36:	00230513          	addi	a0,t1,2
1c00ac3a:	00088763          	beqz	a7,1c00ac48 <pos_libc_prf+0x1aa4>
1c00ac3e:	fa9042e3          	bgtz	s1,1c00abe2 <pos_libc_prf+0x1a3e>
1c00ac42:	4a01                	li	s4,0
1c00ac44:	cc02                	sw	zero,24(sp)
1c00ac46:	bdf1                	j	1c00ab22 <pos_libc_prf+0x197e>
1c00ac48:	fe905de3          	blez	s1,1c00ac42 <pos_libc_prf+0x1a9e>
1c00ac4c:	85aa                	mv	a1,a0
1c00ac4e:	4a01                	li	s4,0
1c00ac50:	cc02                	sw	zero,24(sp)
1c00ac52:	8326                	mv	t1,s1
1c00ac54:	4841                	li	a6,16
1c00ac56:	b4b5                	j	1c00a6c2 <pos_libc_prf+0x151e>
1c00ac58:	02e00593          	li	a1,46
1c00ac5c:	00b50023          	sb	a1,0(a0)
1c00ac60:	88d2                	mv	a7,s4
1c00ac62:	0505                	addi	a0,a0,1
1c00ac64:	8a46                	mv	s4,a7
1c00ac66:	85aa                	mv	a1,a0
1c00ac68:	8326                	mv	t1,s1
1c00ac6a:	cc02                	sw	zero,24(sp)
1c00ac6c:	4881                	li	a7,0
1c00ac6e:	bc81                	j	1c00a6be <pos_libc_prf+0x151a>
1c00ac70:	4a01                	li	s4,0
1c00ac72:	483d                	li	a6,15
1c00ac74:	b43d                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00ac76:	00e30513          	addi	a0,t1,14
1c00ac7a:	4809                	li	a6,2
1c00ac7c:	b41d                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00ac7e:	00c30513          	addi	a0,t1,12
1c00ac82:	b405                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00ac84:	c0200813          	li	a6,-1022
1c00ac88:	a62ff06f          	j	1c009eea <pos_libc_prf+0xd46>
1c00ac8c:	00330513          	addi	a0,t1,3
1c00ac90:	4835                	li	a6,13
1c00ac92:	bc01                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00ac94:	00230513          	addi	a0,t1,2
1c00ac98:	4a01                	li	s4,0
1c00ac9a:	4839                	li	a6,14
1c00ac9c:	b419                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00ac9e:	00b30513          	addi	a0,t1,11
1c00aca2:	4815                	li	a6,5
1c00aca4:	bafd                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00aca6:	00a30513          	addi	a0,t1,10
1c00acaa:	4819                	li	a6,6
1c00acac:	badd                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00acae:	00930513          	addi	a0,t1,9
1c00acb2:	481d                	li	a6,7
1c00acb4:	b2fd                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00acb6:	00830513          	addi	a0,t1,8
1c00acba:	4821                	li	a6,8
1c00acbc:	b2dd                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00acbe:	00730513          	addi	a0,t1,7
1c00acc2:	4825                	li	a6,9
1c00acc4:	baf9                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00acc6:	00630513          	addi	a0,t1,6
1c00acca:	4829                	li	a6,10
1c00accc:	bad9                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00acce:	00530513          	addi	a0,t1,5
1c00acd2:	482d                	li	a6,11
1c00acd4:	b2f9                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00acd6:	00430513          	addi	a0,t1,4
1c00acda:	4831                	li	a6,12
1c00acdc:	b2d9                	j	1c00a6a2 <pos_libc_prf+0x14fe>
1c00acde:	849a                	mv	s1,t1
1c00ace0:	852e                	mv	a0,a1
1c00ace2:	b581                	j	1c00ab22 <pos_libc_prf+0x197e>
1c00ace4:	41990933          	sub	s2,s2,s9
1c00ace8:	8f3fe06f          	j	1c0095da <pos_libc_prf+0x436>
1c00acec:	00d78513          	addi	a0,a5,13
1c00acf0:	804ff06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00acf4:	00c78513          	addi	a0,a5,12
1c00acf8:	ffdfe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00acfc:	00b78513          	addi	a0,a5,11
1c00ad00:	ff5fe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad04:	00978513          	addi	a0,a5,9
1c00ad08:	fedfe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad0c:	00878513          	addi	a0,a5,8
1c00ad10:	fe5fe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad14:	00778513          	addi	a0,a5,7
1c00ad18:	fddfe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad1c:	00678513          	addi	a0,a5,6
1c00ad20:	fd5fe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad24:	00578513          	addi	a0,a5,5
1c00ad28:	fcdfe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad2c:	00478513          	addi	a0,a5,4
1c00ad30:	fc5fe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad34:	00378513          	addi	a0,a5,3
1c00ad38:	fbdfe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad3c:	00278513          	addi	a0,a5,2
1c00ad40:	fb5fe06f          	j	1c009cf4 <pos_libc_prf+0xb50>
1c00ad44:	00178513          	addi	a0,a5,1
1c00ad48:	4c81                	li	s9,0
1c00ad4a:	fabfe06f          	j	1c009cf4 <pos_libc_prf+0xb50>

1c00ad4e <pos_init_start>:
1c00ad4e:	1141                	addi	sp,sp,-16
1c00ad50:	c422                	sw	s0,8(sp)
1c00ad52:	1c001437          	lui	s0,0x1c001
1c00ad56:	c606                	sw	ra,12(sp)
1c00ad58:	84c40413          	addi	s0,s0,-1972 # 1c00084c <ctor_list>
1c00ad5c:	2c79                	jal	1c00affa <pos_irq_init>
1c00ad5e:	b1afe0ef          	jal	ra,1c009078 <pos_soc_init>
1c00ad62:	24e9                	jal	1c00b02c <pos_soc_event_init>
1c00ad64:	2a65                	jal	1c00af1c <pos_allocs_init>
1c00ad66:	284d                	jal	1c00ae18 <pos_sched_init>
1c00ad68:	405c                	lw	a5,4(s0)
1c00ad6a:	c791                	beqz	a5,1c00ad76 <pos_init_start+0x28>
1c00ad6c:	0421                	addi	s0,s0,8
1c00ad6e:	9782                	jalr	a5
1c00ad70:	0044278b          	p.lw	a5,4(s0!)
1c00ad74:	ffed                	bnez	a5,1c00ad6e <pos_init_start+0x20>
1c00ad76:	bf8fe0ef          	jal	ra,1c00916e <pos_io_start>
1c00ad7a:	300467f3          	csrrsi	a5,mstatus,8
1c00ad7e:	40b2                	lw	ra,12(sp)
1c00ad80:	4422                	lw	s0,8(sp)
1c00ad82:	0141                	addi	sp,sp,16
1c00ad84:	8082                	ret

1c00ad86 <pos_init_stop>:
1c00ad86:	1141                	addi	sp,sp,-16
1c00ad88:	c422                	sw	s0,8(sp)
1c00ad8a:	1c001437          	lui	s0,0x1c001
1c00ad8e:	c606                	sw	ra,12(sp)
1c00ad90:	86040413          	addi	s0,s0,-1952 # 1c000860 <dtor_list>
1c00ad94:	bdefe0ef          	jal	ra,1c009172 <pos_io_stop>
1c00ad98:	405c                	lw	a5,4(s0)
1c00ad9a:	c791                	beqz	a5,1c00ada6 <pos_init_stop+0x20>
1c00ad9c:	0421                	addi	s0,s0,8
1c00ad9e:	9782                	jalr	a5
1c00ada0:	0044278b          	p.lw	a5,4(s0!)
1c00ada4:	ffed                	bnez	a5,1c00ad9e <pos_init_stop+0x18>
1c00ada6:	40b2                	lw	ra,12(sp)
1c00ada8:	4422                	lw	s0,8(sp)
1c00adaa:	0141                	addi	sp,sp,16
1c00adac:	8082                	ret

1c00adae <pos_cbsys_add>:
1c00adae:	00259793          	slli	a5,a1,0x2
1c00adb2:	1c0015b7          	lui	a1,0x1c001
1c00adb6:	3e058593          	addi	a1,a1,992 # 1c0013e0 <stack>
1c00adba:	95be                	add	a1,a1,a5
1c00adbc:	419c                	lw	a5,0(a1)
1c00adbe:	c110                	sw	a2,0(a0)
1c00adc0:	c154                	sw	a3,4(a0)
1c00adc2:	c51c                	sw	a5,8(a0)
1c00adc4:	c188                	sw	a0,0(a1)
1c00adc6:	8082                	ret

1c00adc8 <pi_open_from_conf>:
1c00adc8:	c14c                	sw	a1,4(a0)
1c00adca:	8082                	ret

1c00adcc <pos_task_handle_blocking>:
1c00adcc:	4785                	li	a5,1
1c00adce:	00f50a23          	sb	a5,20(a0)
1c00add2:	8082                	ret

1c00add4 <pos_task_handle>:
1c00add4:	1141                	addi	sp,sp,-16
1c00add6:	c422                	sw	s0,8(sp)
1c00add8:	02000413          	li	s0,32
1c00addc:	401c                	lw	a5,0(s0)
1c00adde:	c606                	sw	ra,12(sp)
1c00ade0:	c385                	beqz	a5,1c00ae00 <pos_task_handle+0x2c>
1c00ade2:	4394                	lw	a3,0(a5)
1c00ade4:	43d8                	lw	a4,4(a5)
1c00ade6:	c014                	sw	a3,0(s0)
1c00ade8:	4788                	lw	a0,8(a5)
1c00adea:	300467f3          	csrrsi	a5,mstatus,8
1c00adee:	9702                	jalr	a4
1c00adf0:	300477f3          	csrrci	a5,mstatus,8
1c00adf4:	401c                	lw	a5,0(s0)
1c00adf6:	f7f5                	bnez	a5,1c00ade2 <pos_task_handle+0xe>
1c00adf8:	40b2                	lw	ra,12(sp)
1c00adfa:	4422                	lw	s0,8(sp)
1c00adfc:	0141                	addi	sp,sp,16
1c00adfe:	8082                	ret
1c00ae00:	10500073          	wfi
1c00ae04:	300467f3          	csrrsi	a5,mstatus,8
1c00ae08:	300477f3          	csrrci	a5,mstatus,8
1c00ae0c:	401c                	lw	a5,0(s0)
1c00ae0e:	fbf1                	bnez	a5,1c00ade2 <pos_task_handle+0xe>
1c00ae10:	40b2                	lw	ra,12(sp)
1c00ae12:	4422                	lw	s0,8(sp)
1c00ae14:	0141                	addi	sp,sp,16
1c00ae16:	8082                	ret

1c00ae18 <pos_sched_init>:
1c00ae18:	02002023          	sw	zero,32(zero) # 20 <pos_sched_first>
1c00ae1c:	8082                	ret

1c00ae1e <pos_alloc_init>:
1c00ae1e:	00758793          	addi	a5,a1,7
1c00ae22:	c407b7b3          	p.bclr	a5,a5,2,0
1c00ae26:	40b785b3          	sub	a1,a5,a1
1c00ae2a:	c11c                	sw	a5,0(a0)
1c00ae2c:	8e0d                	sub	a2,a2,a1
1c00ae2e:	00c05763          	blez	a2,1c00ae3c <pos_alloc_init+0x1e>
1c00ae32:	c4063633          	p.bclr	a2,a2,2,0
1c00ae36:	c390                	sw	a2,0(a5)
1c00ae38:	0007a223          	sw	zero,4(a5)
1c00ae3c:	8082                	ret

1c00ae3e <pos_alloc>:
1c00ae3e:	4110                	lw	a2,0(a0)
1c00ae40:	059d                	addi	a1,a1,7
1c00ae42:	c405b5b3          	p.bclr	a1,a1,2,0
1c00ae46:	ca31                	beqz	a2,1c00ae9a <pos_alloc+0x5c>
1c00ae48:	4218                	lw	a4,0(a2)
1c00ae4a:	425c                	lw	a5,4(a2)
1c00ae4c:	02b75963          	ble	a1,a4,1c00ae7e <pos_alloc+0x40>
1c00ae50:	cb81                	beqz	a5,1c00ae60 <pos_alloc+0x22>
1c00ae52:	4398                	lw	a4,0(a5)
1c00ae54:	43d4                	lw	a3,4(a5)
1c00ae56:	00b75763          	ble	a1,a4,1c00ae64 <pos_alloc+0x26>
1c00ae5a:	863e                	mv	a2,a5
1c00ae5c:	87b6                	mv	a5,a3
1c00ae5e:	fbf5                	bnez	a5,1c00ae52 <pos_alloc+0x14>
1c00ae60:	853e                	mv	a0,a5
1c00ae62:	8082                	ret
1c00ae64:	00b70a63          	beq	a4,a1,1c00ae78 <pos_alloc+0x3a>
1c00ae68:	00b78533          	add	a0,a5,a1
1c00ae6c:	8f0d                	sub	a4,a4,a1
1c00ae6e:	c118                	sw	a4,0(a0)
1c00ae70:	c154                	sw	a3,4(a0)
1c00ae72:	c248                	sw	a0,4(a2)
1c00ae74:	853e                	mv	a0,a5
1c00ae76:	8082                	ret
1c00ae78:	c254                	sw	a3,4(a2)
1c00ae7a:	853e                	mv	a0,a5
1c00ae7c:	8082                	ret
1c00ae7e:	00e58b63          	beq	a1,a4,1c00ae94 <pos_alloc+0x56>
1c00ae82:	00b606b3          	add	a3,a2,a1
1c00ae86:	8f0d                	sub	a4,a4,a1
1c00ae88:	c2dc                	sw	a5,4(a3)
1c00ae8a:	c298                	sw	a4,0(a3)
1c00ae8c:	87b2                	mv	a5,a2
1c00ae8e:	c114                	sw	a3,0(a0)
1c00ae90:	853e                	mv	a0,a5
1c00ae92:	8082                	ret
1c00ae94:	c11c                	sw	a5,0(a0)
1c00ae96:	87b2                	mv	a5,a2
1c00ae98:	b7e1                	j	1c00ae60 <pos_alloc+0x22>
1c00ae9a:	4781                	li	a5,0
1c00ae9c:	b7d1                	j	1c00ae60 <pos_alloc+0x22>

1c00ae9e <pos_free>:
1c00ae9e:	4118                	lw	a4,0(a0)
1c00aea0:	061d                	addi	a2,a2,7
1c00aea2:	c4063633          	p.bclr	a2,a2,2,0
1c00aea6:	c729                	beqz	a4,1c00aef0 <pos_free+0x52>
1c00aea8:	00b76663          	bltu	a4,a1,1c00aeb4 <pos_free+0x16>
1c00aeac:	a0a1                	j	1c00aef4 <pos_free+0x56>
1c00aeae:	00b7f563          	bleu	a1,a5,1c00aeb8 <pos_free+0x1a>
1c00aeb2:	873e                	mv	a4,a5
1c00aeb4:	435c                	lw	a5,4(a4)
1c00aeb6:	ffe5                	bnez	a5,1c00aeae <pos_free+0x10>
1c00aeb8:	00c586b3          	add	a3,a1,a2
1c00aebc:	02d78463          	beq	a5,a3,1c00aee4 <pos_free+0x46>
1c00aec0:	c190                	sw	a2,0(a1)
1c00aec2:	c1dc                	sw	a5,4(a1)
1c00aec4:	cf11                	beqz	a4,1c00aee0 <pos_free+0x42>
1c00aec6:	431c                	lw	a5,0(a4)
1c00aec8:	00f706b3          	add	a3,a4,a5
1c00aecc:	00d58463          	beq	a1,a3,1c00aed4 <pos_free+0x36>
1c00aed0:	c34c                	sw	a1,4(a4)
1c00aed2:	8082                	ret
1c00aed4:	4194                	lw	a3,0(a1)
1c00aed6:	41d0                	lw	a2,4(a1)
1c00aed8:	97b6                	add	a5,a5,a3
1c00aeda:	c31c                	sw	a5,0(a4)
1c00aedc:	c350                	sw	a2,4(a4)
1c00aede:	8082                	ret
1c00aee0:	c10c                	sw	a1,0(a0)
1c00aee2:	8082                	ret
1c00aee4:	4394                	lw	a3,0(a5)
1c00aee6:	43dc                	lw	a5,4(a5)
1c00aee8:	9636                	add	a2,a2,a3
1c00aeea:	c190                	sw	a2,0(a1)
1c00aeec:	c1dc                	sw	a5,4(a1)
1c00aeee:	bfd9                	j	1c00aec4 <pos_free+0x26>
1c00aef0:	4781                	li	a5,0
1c00aef2:	b7d9                	j	1c00aeb8 <pos_free+0x1a>
1c00aef4:	87ba                	mv	a5,a4
1c00aef6:	4701                	li	a4,0
1c00aef8:	b7c1                	j	1c00aeb8 <pos_free+0x1a>

1c00aefa <pos_alloc_init_l1>:
1c00aefa:	1c0077b7          	lui	a5,0x1c007
1c00aefe:	4247a703          	lw	a4,1060(a5) # 1c007424 <pos_alloc_l1>
1c00af02:	100007b7          	lui	a5,0x10000
1c00af06:	01751593          	slli	a1,a0,0x17
1c00af0a:	6641                	lui	a2,0x10
1c00af0c:	050a                	slli	a0,a0,0x2
1c00af0e:	03078793          	addi	a5,a5,48 # 10000030 <__l1_end>
1c00af12:	fd060613          	addi	a2,a2,-48 # ffd0 <__l1_heap_size>
1c00af16:	95be                	add	a1,a1,a5
1c00af18:	953a                	add	a0,a0,a4
1c00af1a:	b711                	j	1c00ae1e <pos_alloc_init>

1c00af1c <pos_allocs_init>:
1c00af1c:	1141                	addi	sp,sp,-16
1c00af1e:	1c0075b7          	lui	a1,0x1c007
1c00af22:	c606                	sw	ra,12(sp)
1c00af24:	c422                	sw	s0,8(sp)
1c00af26:	45058793          	addi	a5,a1,1104 # 1c007450 <__l2_priv0_end>
1c00af2a:	1c008637          	lui	a2,0x1c008
1c00af2e:	04c7c363          	blt	a5,a2,1c00af74 <pos_allocs_init+0x58>
1c00af32:	4581                	li	a1,0
1c00af34:	4601                	li	a2,0
1c00af36:	1c007437          	lui	s0,0x1c007
1c00af3a:	42840513          	addi	a0,s0,1064 # 1c007428 <pos_alloc_l2>
1c00af3e:	35c5                	jal	1c00ae1e <pos_alloc_init>
1c00af40:	1c0105b7          	lui	a1,0x1c010
1c00af44:	1b458793          	addi	a5,a1,436 # 1c0101b4 <__l2_shared_end>
1c00af48:	1c080637          	lui	a2,0x1c080
1c00af4c:	1c007537          	lui	a0,0x1c007
1c00af50:	8e1d                	sub	a2,a2,a5
1c00af52:	1b458593          	addi	a1,a1,436
1c00af56:	42c50513          	addi	a0,a0,1068 # 1c00742c <pos_alloc_l2+0x4>
1c00af5a:	35d1                	jal	1c00ae1e <pos_alloc_init>
1c00af5c:	42840513          	addi	a0,s0,1064
1c00af60:	4591                	li	a1,4
1c00af62:	3df1                	jal	1c00ae3e <pos_alloc>
1c00af64:	40b2                	lw	ra,12(sp)
1c00af66:	4422                	lw	s0,8(sp)
1c00af68:	1c0077b7          	lui	a5,0x1c007
1c00af6c:	42a7a223          	sw	a0,1060(a5) # 1c007424 <pos_alloc_l1>
1c00af70:	0141                	addi	sp,sp,16
1c00af72:	8082                	ret
1c00af74:	8e1d                	sub	a2,a2,a5
1c00af76:	45058593          	addi	a1,a1,1104
1c00af7a:	bf75                	j	1c00af36 <pos_allocs_init+0x1a>

1c00af7c <pi_cl_l1_malloc>:
1c00af7c:	4781                	li	a5,0
1c00af7e:	c509                	beqz	a0,1c00af88 <pi_cl_l1_malloc+0xc>
1c00af80:	451c                	lw	a5,8(a0)
1c00af82:	01c7c783          	lbu	a5,28(a5)
1c00af86:	078a                	slli	a5,a5,0x2
1c00af88:	1c007737          	lui	a4,0x1c007
1c00af8c:	42472503          	lw	a0,1060(a4) # 1c007424 <pos_alloc_l1>
1c00af90:	953e                	add	a0,a0,a5
1c00af92:	b575                	j	1c00ae3e <pos_alloc>

1c00af94 <pi_cl_l1_free>:
1c00af94:	4781                	li	a5,0
1c00af96:	c509                	beqz	a0,1c00afa0 <pi_cl_l1_free+0xc>
1c00af98:	451c                	lw	a5,8(a0)
1c00af9a:	01c7c783          	lbu	a5,28(a5)
1c00af9e:	078a                	slli	a5,a5,0x2
1c00afa0:	1c007737          	lui	a4,0x1c007
1c00afa4:	42472503          	lw	a0,1060(a4) # 1c007424 <pos_alloc_l1>
1c00afa8:	953e                	add	a0,a0,a5
1c00afaa:	bdd5                	j	1c00ae9e <pos_free>

1c00afac <pos_irq_set_handler>:
1c00afac:	f14027f3          	csrr	a5,mhartid
1c00afb0:	477d                	li	a4,31
1c00afb2:	ca5797b3          	p.extractu	a5,a5,5,5
1c00afb6:	02e78d63          	beq	a5,a4,1c00aff0 <pos_irq_set_handler+0x44>
1c00afba:	002007b7          	lui	a5,0x200
1c00afbe:	43b8                	lw	a4,64(a5)
1c00afc0:	050a                	slli	a0,a0,0x2
1c00afc2:	8d89                	sub	a1,a1,a0
1c00afc4:	8d99                	sub	a1,a1,a4
1c00afc6:	c14586b3          	p.extract	a3,a1,0,20
1c00afca:	06f00793          	li	a5,111
1c00afce:	c1f6a7b3          	p.insert	a5,a3,0,31
1c00afd2:	d21586b3          	p.extract	a3,a1,9,1
1c00afd6:	d356a7b3          	p.insert	a5,a3,9,21
1c00afda:	c0b586b3          	p.extract	a3,a1,0,11
1c00afde:	c146a7b3          	p.insert	a5,a3,0,20
1c00afe2:	cec585b3          	p.extract	a1,a1,7,12
1c00afe6:	cec5a7b3          	p.insert	a5,a1,7,12
1c00afea:	00f56723          	p.sw	a5,a4(a0)
1c00afee:	8082                	ret
1c00aff0:	30502773          	csrr	a4,mtvec
1c00aff4:	c0073733          	p.bclr	a4,a4,0,0
1c00aff8:	b7e1                	j	1c00afc0 <pos_irq_set_handler+0x14>

1c00affa <pos_irq_init>:
1c00affa:	f1402773          	csrr	a4,mhartid
1c00affe:	1a10a7b7          	lui	a5,0x1a10a
1c00b002:	56fd                	li	a3,-1
1c00b004:	80d7a423          	sw	a3,-2040(a5) # 1a109808 <__l1_end+0xa1097d8>
1c00b008:	ca571733          	p.extractu	a4,a4,5,5
1c00b00c:	1c0087b7          	lui	a5,0x1c008
1c00b010:	46fd                	li	a3,31
1c00b012:	00078793          	mv	a5,a5
1c00b016:	00d70663          	beq	a4,a3,1c00b022 <pos_irq_init+0x28>
1c00b01a:	00200737          	lui	a4,0x200
1c00b01e:	c33c                	sw	a5,64(a4)
1c00b020:	8082                	ret
1c00b022:	c007c7b3          	p.bset	a5,a5,0,0
1c00b026:	30579073          	csrw	mtvec,a5
1c00b02a:	8082                	ret

1c00b02c <pos_soc_event_init>:
1c00b02c:	1a1067b7          	lui	a5,0x1a106
1c00b030:	1141                	addi	sp,sp,-16
1c00b032:	c606                	sw	ra,12(sp)
1c00b034:	577d                	li	a4,-1
1c00b036:	00478693          	addi	a3,a5,4 # 1a106004 <__l1_end+0xa105fd4>
1c00b03a:	c298                	sw	a4,0(a3)
1c00b03c:	00878693          	addi	a3,a5,8
1c00b040:	c298                	sw	a4,0(a3)
1c00b042:	00c78693          	addi	a3,a5,12
1c00b046:	c298                	sw	a4,0(a3)
1c00b048:	01078693          	addi	a3,a5,16
1c00b04c:	c298                	sw	a4,0(a3)
1c00b04e:	01478693          	addi	a3,a5,20
1c00b052:	c298                	sw	a4,0(a3)
1c00b054:	01878693          	addi	a3,a5,24
1c00b058:	c298                	sw	a4,0(a3)
1c00b05a:	01c78693          	addi	a3,a5,28
1c00b05e:	c298                	sw	a4,0(a3)
1c00b060:	02078793          	addi	a5,a5,32
1c00b064:	1c00b5b7          	lui	a1,0x1c00b
1c00b068:	c398                	sw	a4,0(a5)
1c00b06a:	68458593          	addi	a1,a1,1668 # 1c00b684 <pos_soc_event_handler_asm>
1c00b06e:	4569                	li	a0,26
1c00b070:	3f35                	jal	1c00afac <pos_irq_set_handler>
1c00b072:	40b2                	lw	ra,12(sp)
1c00b074:	1a10a7b7          	lui	a5,0x1a10a
1c00b078:	04000737          	lui	a4,0x4000
1c00b07c:	80e7a223          	sw	a4,-2044(a5) # 1a109804 <__l1_end+0xa1097d4>
1c00b080:	0141                	addi	sp,sp,16
1c00b082:	8082                	ret

1c00b084 <pos_time_poweroff>:
1c00b084:	1a10b7b7          	lui	a5,0x1a10b
1c00b088:	0791                	addi	a5,a5,4
1c00b08a:	0087a783          	lw	a5,8(a5) # 1a10b008 <__l1_end+0xa10afd8>
1c00b08e:	1c001737          	lui	a4,0x1c001
1c00b092:	3ef72c23          	sw	a5,1016(a4) # 1c0013f8 <pos_time_timer_count>
1c00b096:	4501                	li	a0,0
1c00b098:	8082                	ret

1c00b09a <pos_time_poweron>:
1c00b09a:	1c0017b7          	lui	a5,0x1c001
1c00b09e:	3f87a703          	lw	a4,1016(a5) # 1c0013f8 <pos_time_timer_count>
1c00b0a2:	1a10b7b7          	lui	a5,0x1a10b
1c00b0a6:	0791                	addi	a5,a5,4
1c00b0a8:	00e7a423          	sw	a4,8(a5) # 1a10b008 <__l1_end+0xa10afd8>
1c00b0ac:	4501                	li	a0,0
1c00b0ae:	8082                	ret

1c00b0b0 <pos_time_timer_handler>:
1c00b0b0:	1c0018b7          	lui	a7,0x1c001
1c00b0b4:	3f888893          	addi	a7,a7,1016 # 1c0013f8 <pos_time_timer_count>
1c00b0b8:	0048a783          	lw	a5,4(a7)
1c00b0bc:	1a10b637          	lui	a2,0x1a10b
1c00b0c0:	0611                	addi	a2,a2,4
1c00b0c2:	00862603          	lw	a2,8(a2) # 1a10b008 <__l1_end+0xa10afd8>
1c00b0c6:	cba9                	beqz	a5,1c00b118 <pos_time_timer_handler+0x68>
1c00b0c8:	5fd8                	lw	a4,60(a5)
1c00b0ca:	800005b7          	lui	a1,0x80000
1c00b0ce:	40e60733          	sub	a4,a2,a4
1c00b0d2:	ffe5c593          	xori	a1,a1,-2
1c00b0d6:	0ae5e763          	bltu	a1,a4,1c00b184 <pos_time_timer_handler+0xd4>
1c00b0da:	02002803          	lw	a6,32(zero) # 20 <pos_sched_first>
1c00b0de:	02402503          	lw	a0,36(zero) # 24 <pos_sched_last>
1c00b0e2:	4398                	lw	a4,0(a5)
1c00b0e4:	0007a023          	sw	zero,0(a5)
1c00b0e8:	4301                	li	t1,0
1c00b0ea:	02080063          	beqz	a6,1c00b10a <pos_time_timer_handler+0x5a>
1c00b0ee:	c11c                	sw	a5,0(a0)
1c00b0f0:	c305                	beqz	a4,1c00b110 <pos_time_timer_handler+0x60>
1c00b0f2:	5f54                	lw	a3,60(a4)
1c00b0f4:	853e                	mv	a0,a5
1c00b0f6:	40d606b3          	sub	a3,a2,a3
1c00b0fa:	04d5e763          	bltu	a1,a3,1c00b148 <pos_time_timer_handler+0x98>
1c00b0fe:	87ba                	mv	a5,a4
1c00b100:	4398                	lw	a4,0(a5)
1c00b102:	0007a023          	sw	zero,0(a5)
1c00b106:	fe0814e3          	bnez	a6,1c00b0ee <pos_time_timer_handler+0x3e>
1c00b10a:	883e                	mv	a6,a5
1c00b10c:	4305                	li	t1,1
1c00b10e:	f375                	bnez	a4,1c00b0f2 <pos_time_timer_handler+0x42>
1c00b110:	06031c63          	bnez	t1,1c00b188 <pos_time_timer_handler+0xd8>
1c00b114:	02f02223          	sw	a5,36(zero) # 24 <pos_sched_last>
1c00b118:	1a10b7b7          	lui	a5,0x1a10b
1c00b11c:	08100713          	li	a4,129
1c00b120:	0791                	addi	a5,a5,4
1c00b122:	0008a223          	sw	zero,4(a7)
1c00b126:	00e7a023          	sw	a4,0(a5) # 1a10b000 <__l1_end+0xa10afd0>
1c00b12a:	f14027f3          	csrr	a5,mhartid
1c00b12e:	477d                	li	a4,31
1c00b130:	ca5797b3          	p.extractu	a5,a5,5,5
1c00b134:	04e78063          	beq	a5,a4,1c00b174 <pos_time_timer_handler+0xc4>
1c00b138:	6785                	lui	a5,0x1
1c00b13a:	80078793          	addi	a5,a5,-2048 # 800 <pos_soc_event_callback+0x3b8>
1c00b13e:	00204737          	lui	a4,0x204
1c00b142:	02f72423          	sw	a5,40(a4) # 204028 <__l1_heap_size+0x1f4058>
1c00b146:	8082                	ret
1c00b148:	04031363          	bnez	t1,1c00b18e <pos_time_timer_handler+0xde>
1c00b14c:	02f02223          	sw	a5,36(zero) # 24 <pos_sched_last>
1c00b150:	1a10b7b7          	lui	a5,0x1a10b
1c00b154:	0791                	addi	a5,a5,4
1c00b156:	00e8a223          	sw	a4,4(a7)
1c00b15a:	0087a683          	lw	a3,8(a5) # 1a10b008 <__l1_end+0xa10afd8>
1c00b15e:	5f58                	lw	a4,60(a4)
1c00b160:	40c70633          	sub	a2,a4,a2
1c00b164:	9636                	add	a2,a2,a3
1c00b166:	00c7a823          	sw	a2,16(a5)
1c00b16a:	08500713          	li	a4,133
1c00b16e:	00e7a023          	sw	a4,0(a5)
1c00b172:	8082                	ret
1c00b174:	6785                	lui	a5,0x1
1c00b176:	1a10a737          	lui	a4,0x1a10a
1c00b17a:	80078793          	addi	a5,a5,-2048 # 800 <pos_soc_event_callback+0x3b8>
1c00b17e:	80f72a23          	sw	a5,-2028(a4) # 1a109814 <__l1_end+0xa1097e4>
1c00b182:	8082                	ret
1c00b184:	873e                	mv	a4,a5
1c00b186:	b7e9                	j	1c00b150 <pos_time_timer_handler+0xa0>
1c00b188:	03002023          	sw	a6,32(zero) # 20 <pos_sched_first>
1c00b18c:	b761                	j	1c00b114 <pos_time_timer_handler+0x64>
1c00b18e:	03002023          	sw	a6,32(zero) # 20 <pos_sched_first>
1c00b192:	bf6d                	j	1c00b14c <pos_time_timer_handler+0x9c>

1c00b194 <pos_time_init>:
1c00b194:	1141                	addi	sp,sp,-16
1c00b196:	c422                	sw	s0,8(sp)
1c00b198:	1a10b7b7          	lui	a5,0x1a10b
1c00b19c:	1c001437          	lui	s0,0x1c001
1c00b1a0:	c606                	sw	ra,12(sp)
1c00b1a2:	3f840413          	addi	s0,s0,1016 # 1c0013f8 <pos_time_timer_count>
1c00b1a6:	08300713          	li	a4,131
1c00b1aa:	0791                	addi	a5,a5,4
1c00b1ac:	00042223          	sw	zero,4(s0)
1c00b1b0:	00e7a023          	sw	a4,0(a5) # 1a10b000 <__l1_end+0xa10afd0>
1c00b1b4:	1c00b5b7          	lui	a1,0x1c00b
1c00b1b8:	66058593          	addi	a1,a1,1632 # 1c00b660 <pos_time_timer_handler_asm>
1c00b1bc:	452d                	li	a0,11
1c00b1be:	33fd                	jal	1c00afac <pos_irq_set_handler>
1c00b1c0:	6785                	lui	a5,0x1
1c00b1c2:	1a10a737          	lui	a4,0x1a10a
1c00b1c6:	80078793          	addi	a5,a5,-2048 # 800 <pos_soc_event_callback+0x3b8>
1c00b1ca:	1c00b637          	lui	a2,0x1c00b
1c00b1ce:	00840513          	addi	a0,s0,8
1c00b1d2:	4681                	li	a3,0
1c00b1d4:	08460613          	addi	a2,a2,132 # 1c00b084 <pos_time_poweroff>
1c00b1d8:	4589                	li	a1,2
1c00b1da:	80f72223          	sw	a5,-2044(a4) # 1a109804 <__l1_end+0xa1097d4>
1c00b1de:	3ec1                	jal	1c00adae <pos_cbsys_add>
1c00b1e0:	01840513          	addi	a0,s0,24
1c00b1e4:	4422                	lw	s0,8(sp)
1c00b1e6:	40b2                	lw	ra,12(sp)
1c00b1e8:	1c00b637          	lui	a2,0x1c00b
1c00b1ec:	4681                	li	a3,0
1c00b1ee:	09a60613          	addi	a2,a2,154 # 1c00b09a <pos_time_poweron>
1c00b1f2:	458d                	li	a1,3
1c00b1f4:	0141                	addi	sp,sp,16
1c00b1f6:	be65                	j	1c00adae <pos_cbsys_add>

1c00b1f8 <pos_uart_init>:
1c00b1f8:	1c0107b7          	lui	a5,0x1c010
1c00b1fc:	1407a823          	sw	zero,336(a5) # 1c010150 <__cluster_text_end>
1c00b200:	8082                	ret

1c00b202 <pi_cluster_conf_init>:
1c00b202:	00052223          	sw	zero,4(a0)
1c00b206:	00052a23          	sw	zero,20(a0)
1c00b20a:	8082                	ret

1c00b20c <pi_cluster_open>:
1c00b20c:	7179                	addi	sp,sp,-48
1c00b20e:	c85a                	sw	s6,16(sp)
1c00b210:	00452b03          	lw	s6,4(a0)
1c00b214:	ca56                	sw	s5,20(sp)
1c00b216:	004b2a83          	lw	s5,4(s6)
1c00b21a:	1c0077b7          	lui	a5,0x1c007
1c00b21e:	d422                	sw	s0,40(sp)
1c00b220:	c462                	sw	s8,8(sp)
1c00b222:	43078413          	addi	s0,a5,1072 # 1c007430 <pos_cluster>
1c00b226:	005a9c13          	slli	s8,s5,0x5
1c00b22a:	d606                	sw	ra,44(sp)
1c00b22c:	d226                	sw	s1,36(sp)
1c00b22e:	d04a                	sw	s2,32(sp)
1c00b230:	ce4e                	sw	s3,28(sp)
1c00b232:	cc52                	sw	s4,24(sp)
1c00b234:	c65e                	sw	s7,12(sp)
1c00b236:	018404b3          	add	s1,s0,s8
1c00b23a:	c504                	sw	s1,8(a0)
1c00b23c:	1c00b5b7          	lui	a1,0x1c00b
1c00b240:	0ffafb93          	andi	s7,s5,255
1c00b244:	5d058593          	addi	a1,a1,1488 # 1c00b5d0 <pos_task_remote_enqueue>
1c00b248:	4505                	li	a0,1
1c00b24a:	01748e23          	sb	s7,28(s1)
1c00b24e:	3bb9                	jal	1c00afac <pos_irq_set_handler>
1c00b250:	020a8793          	addi	a5,s5,32
1c00b254:	1a10a737          	lui	a4,0x1a10a
1c00b258:	01779993          	slli	s3,a5,0x17
1c00b25c:	00400913          	li	s2,4
1c00b260:	4789                	li	a5,2
1c00b262:	80f72223          	sw	a5,-2044(a4) # 1a109804 <__l1_end+0xa1097d4>
1c00b266:	e6c93933          	p.bclr	s2,s2,19,12
1c00b26a:	0004a023          	sw	zero,0(s1)
1c00b26e:	994e                	add	s2,s2,s3
1c00b270:	10000a37          	lui	s4,0x10000
1c00b274:	00092023          	sw	zero,0(s2)
1c00b278:	028a0a13          	addi	s4,s4,40 # 10000028 <pos_cluster_fc_task_lock>
1c00b27c:	4509                	li	a0,2
1c00b27e:	00092623          	sw	zero,12(s2)
1c00b282:	00092223          	sw	zero,4(s2)
1c00b286:	000a2023          	sw	zero,0(s4)
1c00b28a:	d01fd0ef          	jal	ra,1c008f8a <pos_fll_init>
1c00b28e:	01400793          	li	a5,20
1c00b292:	478c                	lw	a1,8(a5)
1c00b294:	e9f1                	bnez	a1,1c00b368 <pi_cluster_open+0x15c>
1c00b296:	c788                	sw	a0,8(a5)
1c00b298:	002004b7          	lui	s1,0x200
1c00b29c:	94ce                	add	s1,s1,s3
1c00b29e:	4785                	li	a5,1
1c00b2a0:	02f4a023          	sw	a5,32(s1) # 200020 <__l1_heap_size+0x1f0050>
1c00b2a4:	00400693          	li	a3,4
1c00b2a8:	e6c6b6b3          	p.bclr	a3,a3,19,12
1c00b2ac:	02c00793          	li	a5,44
1c00b2b0:	96ce                	add	a3,a3,s3
1c00b2b2:	02f05563          	blez	a5,1c00b2dc <pi_cluster_open+0xd0>
1c00b2b6:	17fd                	addi	a5,a5,-1
1c00b2b8:	1c010737          	lui	a4,0x1c010
1c00b2bc:	18870713          	addi	a4,a4,392 # 1c010188 <_l1_preload_start_inL2>
1c00b2c0:	8389                	srli	a5,a5,0x2
1c00b2c2:	02800613          	li	a2,40
1c00b2c6:	55f5                	li	a1,-3
1c00b2c8:	8e99                	sub	a3,a3,a4
1c00b2ca:	0785                	addi	a5,a5,1
1c00b2cc:	0ab64263          	blt	a2,a1,1c00b370 <pi_cluster_open+0x164>
1c00b2d0:	0057c0fb          	lp.setup	x1,a5,1c00b2da <pi_cluster_open+0xce>
1c00b2d4:	4310                	lw	a2,0(a4)
1c00b2d6:	00c766a3          	p.sw	a2,a3(a4)
1c00b2da:	0711                	addi	a4,a4,4
1c00b2dc:	018407b3          	add	a5,s0,s8
1c00b2e0:	01778e23          	sb	s7,28(a5)
1c00b2e4:	00201437          	lui	s0,0x201
1c00b2e8:	014b4683          	lbu	a3,20(s6)
1c00b2ec:	e0440713          	addi	a4,s0,-508 # 200e04 <__l1_heap_size+0x1f0e34>
1c00b2f0:	974e                	add	a4,a4,s3
1c00b2f2:	cf98                	sw	a4,24(a5)
1c00b2f4:	cb98                	sw	a4,16(a5)
1c00b2f6:	0127a223          	sw	s2,4(a5)
1c00b2fa:	00d78ea3          	sb	a3,29(a5)
1c00b2fe:	8556                	mv	a0,s5
1c00b300:	0007a423          	sw	zero,8(a5)
1c00b304:	0007aa23          	sw	zero,20(a5)
1c00b308:	00078f23          	sb	zero,30(a5)
1c00b30c:	00da0223          	sb	a3,4(s4)
1c00b310:	36ed                	jal	1c00aefa <pos_alloc_init_l1>
1c00b312:	40040793          	addi	a5,s0,1024
1c00b316:	97ce                	add	a5,a5,s3
1c00b318:	577d                	li	a4,-1
1c00b31a:	00e7a023          	sw	a4,0(a5)
1c00b31e:	1c0087b7          	lui	a5,0x1c008
1c00b322:	08078793          	addi	a5,a5,128 # 1c008080 <_start>
1c00b326:	04f4a023          	sw	a5,64(s1)
1c00b32a:	04f4a223          	sw	a5,68(s1)
1c00b32e:	04f4a423          	sw	a5,72(s1)
1c00b332:	04f4a623          	sw	a5,76(s1)
1c00b336:	04f4a823          	sw	a5,80(s1)
1c00b33a:	04f4aa23          	sw	a5,84(s1)
1c00b33e:	04f4ac23          	sw	a5,88(s1)
1c00b342:	04f4ae23          	sw	a5,92(s1)
1c00b346:	0ff00793          	li	a5,255
1c00b34a:	00f4a423          	sw	a5,8(s1)
1c00b34e:	50b2                	lw	ra,44(sp)
1c00b350:	5422                	lw	s0,40(sp)
1c00b352:	5492                	lw	s1,36(sp)
1c00b354:	5902                	lw	s2,32(sp)
1c00b356:	49f2                	lw	s3,28(sp)
1c00b358:	4a62                	lw	s4,24(sp)
1c00b35a:	4ad2                	lw	s5,20(sp)
1c00b35c:	4b42                	lw	s6,16(sp)
1c00b35e:	4bb2                	lw	s7,12(sp)
1c00b360:	4c22                	lw	s8,8(sp)
1c00b362:	4501                	li	a0,0
1c00b364:	6145                	addi	sp,sp,48
1c00b366:	8082                	ret
1c00b368:	4509                	li	a0,2
1c00b36a:	bc7fd0ef          	jal	ra,1c008f30 <pos_fll_set_freq>
1c00b36e:	b72d                	j	1c00b298 <pi_cluster_open+0x8c>
1c00b370:	4785                	li	a5,1
1c00b372:	bfb9                	j	1c00b2d0 <pi_cluster_open+0xc4>

1c00b374 <pi_cluster_close>:
1c00b374:	4501                	li	a0,0
1c00b376:	8082                	ret

1c00b378 <pos_cluster_task_set_stack>:
1c00b378:	1101                	addi	sp,sp,-32
1c00b37a:	c84a                	sw	s2,16(sp)
1c00b37c:	00852903          	lw	s2,8(a0)
1c00b380:	ca26                	sw	s1,20(sp)
1c00b382:	c64e                	sw	s3,12(sp)
1c00b384:	4785                	li	a5,1
1c00b386:	ce06                	sw	ra,28(sp)
1c00b388:	cc22                	sw	s0,24(sp)
1c00b38a:	00f90f23          	sb	a5,30(s2)
1c00b38e:	45dc                	lw	a5,12(a1)
1c00b390:	89aa                	mv	s3,a0
1c00b392:	84ae                	mv	s1,a1
1c00b394:	ebb1                	bnez	a5,1c00b3e8 <pos_cluster_task_set_stack+0x70>
1c00b396:	6785                	lui	a5,0x1
1c00b398:	80078793          	addi	a5,a5,-2048 # 800 <pos_soc_event_callback+0x3b8>
1c00b39c:	40000713          	li	a4,1024
1c00b3a0:	c5dc                	sw	a5,12(a1)
1c00b3a2:	c998                	sw	a4,16(a1)
1c00b3a4:	40000693          	li	a3,1024
1c00b3a8:	48d8                	lw	a4,20(s1)
1c00b3aa:	00892503          	lw	a0,8(s2)
1c00b3ae:	177d                	addi	a4,a4,-1
1c00b3b0:	843e                	mv	s0,a5
1c00b3b2:	42d70433          	p.mac	s0,a4,a3
1c00b3b6:	c901                	beqz	a0,1c00b3c6 <pos_cluster_task_set_stack+0x4e>
1c00b3b8:	00c92603          	lw	a2,12(s2)
1c00b3bc:	00860d63          	beq	a2,s0,1c00b3d6 <pos_cluster_task_set_stack+0x5e>
1c00b3c0:	85aa                	mv	a1,a0
1c00b3c2:	854e                	mv	a0,s3
1c00b3c4:	3ec1                	jal	1c00af94 <pi_cl_l1_free>
1c00b3c6:	00892623          	sw	s0,12(s2)
1c00b3ca:	85a2                	mv	a1,s0
1c00b3cc:	854e                	mv	a0,s3
1c00b3ce:	367d                	jal	1c00af7c <pi_cl_l1_malloc>
1c00b3d0:	00a92423          	sw	a0,8(s2)
1c00b3d4:	cd19                	beqz	a0,1c00b3f2 <pos_cluster_task_set_stack+0x7a>
1c00b3d6:	c488                	sw	a0,8(s1)
1c00b3d8:	4501                	li	a0,0
1c00b3da:	40f2                	lw	ra,28(sp)
1c00b3dc:	4462                	lw	s0,24(sp)
1c00b3de:	44d2                	lw	s1,20(sp)
1c00b3e0:	4942                	lw	s2,16(sp)
1c00b3e2:	49b2                	lw	s3,12(sp)
1c00b3e4:	6105                	addi	sp,sp,32
1c00b3e6:	8082                	ret
1c00b3e8:	4994                	lw	a3,16(a1)
1c00b3ea:	fedd                	bnez	a3,1c00b3a8 <pos_cluster_task_set_stack+0x30>
1c00b3ec:	c99c                	sw	a5,16(a1)
1c00b3ee:	86be                	mv	a3,a5
1c00b3f0:	bf65                	j	1c00b3a8 <pos_cluster_task_set_stack+0x30>
1c00b3f2:	557d                	li	a0,-1
1c00b3f4:	b7dd                	j	1c00b3da <pos_cluster_task_set_stack+0x62>

1c00b3f6 <pi_cluster_send_task_to_cl>:
1c00b3f6:	715d                	addi	sp,sp,-80
1c00b3f8:	c2a6                	sw	s1,68(sp)
1c00b3fa:	1c00b7b7          	lui	a5,0x1c00b
1c00b3fe:	4504                	lw	s1,8(a0)
1c00b400:	c4a2                	sw	s0,72(sp)
1c00b402:	c0ca                	sw	s2,64(sp)
1c00b404:	dcc78793          	addi	a5,a5,-564 # 1c00adcc <pos_task_handle_blocking>
1c00b408:	c686                	sw	ra,76(sp)
1c00b40a:	c23e                	sw	a5,4(sp)
1c00b40c:	01d4c703          	lbu	a4,29(s1)
1c00b410:	00010793          	mv	a5,sp
1c00b414:	00010a23          	sb	zero,20(sp)
1c00b418:	c43e                	sw	a5,8(sp)
1c00b41a:	842e                	mv	s0,a1
1c00b41c:	0044a903          	lw	s2,4(s1)
1c00b420:	459c                	lw	a5,8(a1)
1c00b422:	04173c63          	p.bneimm	a4,1,1c00b47a <pi_cluster_send_task_to_cl+0x84>
1c00b426:	c3b5                	beqz	a5,1c00b48a <pi_cluster_send_task_to_cl+0x94>
1c00b428:	00010793          	mv	a5,sp
1c00b42c:	02042023          	sw	zero,32(s0)
1c00b430:	cc1c                	sw	a5,24(s0)
1c00b432:	30047773          	csrrci	a4,mstatus,8
1c00b436:	409c                	lw	a5,0(s1)
1c00b438:	c391                	beqz	a5,1c00b43c <pi_cluster_send_task_to_cl+0x46>
1c00b43a:	d380                	sw	s0,32(a5)
1c00b43c:	c080                	sw	s0,0(s1)
1c00b43e:	00092783          	lw	a5,0(s2)
1c00b442:	cb8d                	beqz	a5,1c00b474 <pi_cluster_send_task_to_cl+0x7e>
1c00b444:	4c9c                	lw	a5,24(s1)
1c00b446:	0007a023          	sw	zero,0(a5)
1c00b44a:	30071073          	csrw	mstatus,a4
1c00b44e:	30047473          	csrrci	s0,mstatus,8
1c00b452:	01410783          	lb	a5,20(sp)
1c00b456:	e791                	bnez	a5,1c00b462 <pi_cluster_send_task_to_cl+0x6c>
1c00b458:	97dff0ef          	jal	ra,1c00add4 <pos_task_handle>
1c00b45c:	01410783          	lb	a5,20(sp)
1c00b460:	dfe5                	beqz	a5,1c00b458 <pi_cluster_send_task_to_cl+0x62>
1c00b462:	30041073          	csrw	mstatus,s0
1c00b466:	4501                	li	a0,0
1c00b468:	40b6                	lw	ra,76(sp)
1c00b46a:	4426                	lw	s0,72(sp)
1c00b46c:	4496                	lw	s1,68(sp)
1c00b46e:	4906                	lw	s2,64(sp)
1c00b470:	6161                	addi	sp,sp,80
1c00b472:	8082                	ret
1c00b474:	00892023          	sw	s0,0(s2)
1c00b478:	b7f1                	j	1c00b444 <pi_cluster_send_task_to_cl+0x4e>
1c00b47a:	cf99                	beqz	a5,1c00b498 <pi_cluster_send_task_to_cl+0xa2>
1c00b47c:	4858                	lw	a4,20(s0)
1c00b47e:	4785                	li	a5,1
1c00b480:	00e797b3          	sll	a5,a5,a4
1c00b484:	17fd                	addi	a5,a5,-1
1c00b486:	d05c                	sw	a5,36(s0)
1c00b488:	b745                	j	1c00b428 <pi_cluster_send_task_to_cl+0x32>
1c00b48a:	01e4c783          	lbu	a5,30(s1)
1c00b48e:	ffc9                	bnez	a5,1c00b428 <pi_cluster_send_task_to_cl+0x32>
1c00b490:	35e5                	jal	1c00b378 <pos_cluster_task_set_stack>
1c00b492:	d959                	beqz	a0,1c00b428 <pi_cluster_send_task_to_cl+0x32>
1c00b494:	557d                	li	a0,-1
1c00b496:	bfc9                	j	1c00b468 <pi_cluster_send_task_to_cl+0x72>
1c00b498:	35c5                	jal	1c00b378 <pos_cluster_task_set_stack>
1c00b49a:	d16d                	beqz	a0,1c00b47c <pi_cluster_send_task_to_cl+0x86>
1c00b49c:	bfe5                	j	1c00b494 <pi_cluster_send_task_to_cl+0x9e>

1c00b49e <pos_init_entry>:
1c00b49e:	cc101073          	csrw	0xcc1,zero
1c00b4a2:	f1402573          	csrr	a0,mhartid
1c00b4a6:	01f57593          	andi	a1,a0,31
1c00b4aa:	8115                	srli	a0,a0,0x5
1c00b4ac:	467d                	li	a2,31
1c00b4ae:	00c50463          	beq	a0,a2,1c00b4b6 <label0>
1c00b4b2:	34f0406f          	j	1c010000 <__cluster_text_start>

1c00b4b6 <label0>:
1c00b4b6:	ffffc297          	auipc	t0,0xffffc
1c00b4ba:	f6a28293          	addi	t0,t0,-150 # 1c007420 <_edata>
1c00b4be:	ffffc317          	auipc	t1,0xffffc
1c00b4c2:	f9230313          	addi	t1,t1,-110 # 1c007450 <__l2_priv0_end>
1c00b4c6:	0002a023          	sw	zero,0(t0)
1c00b4ca:	0291                	addi	t0,t0,4
1c00b4cc:	fe62ede3          	bltu	t0,t1,1c00b4c6 <label0+0x10>
1c00b4d0:	ffff6117          	auipc	sp,0xffff6
1c00b4d4:	f1010113          	addi	sp,sp,-240 # 1c0013e0 <stack>
1c00b4d8:	00000297          	auipc	t0,0x0
1c00b4dc:	87628293          	addi	t0,t0,-1930 # 1c00ad4e <pos_init_start>
1c00b4e0:	000280e7          	jalr	t0
1c00b4e4:	00000513          	li	a0,0
1c00b4e8:	00000593          	li	a1,0
1c00b4ec:	ffffd397          	auipc	t2,0xffffd
1c00b4f0:	73c38393          	addi	t2,t2,1852 # 1c008c28 <main>
1c00b4f4:	000380e7          	jalr	t2
1c00b4f8:	842a                	mv	s0,a0
1c00b4fa:	8522                	mv	a0,s0
1c00b4fc:	ffffe297          	auipc	t0,0xffffe
1c00b500:	c4628293          	addi	t0,t0,-954 # 1c009142 <exit>
1c00b504:	000280e7          	jalr	t0

1c00b508 <pos_irq_call_external_c_function>:
1c00b508:	7119                	addi	sp,sp,-128
1c00b50a:	c006                	sw	ra,0(sp)
1c00b50c:	c20e                	sw	gp,4(sp)
1c00b50e:	c412                	sw	tp,8(sp)
1c00b510:	c616                	sw	t0,12(sp)
1c00b512:	c81a                	sw	t1,16(sp)
1c00b514:	ca1e                	sw	t2,20(sp)
1c00b516:	d236                	sw	a3,36(sp)
1c00b518:	d43a                	sw	a4,40(sp)
1c00b51a:	d63e                	sw	a5,44(sp)
1c00b51c:	d842                	sw	a6,48(sp)
1c00b51e:	da46                	sw	a7,52(sp)
1c00b520:	dc72                	sw	t3,56(sp)
1c00b522:	de76                	sw	t4,60(sp)
1c00b524:	c0fa                	sw	t5,64(sp)
1c00b526:	c6fe                	sw	t6,76(sp)
1c00b528:	000600e7          	jalr	a2
1c00b52c:	4082                	lw	ra,0(sp)
1c00b52e:	4192                	lw	gp,4(sp)
1c00b530:	4222                	lw	tp,8(sp)
1c00b532:	42b2                	lw	t0,12(sp)
1c00b534:	4342                	lw	t1,16(sp)
1c00b536:	43d2                	lw	t2,20(sp)
1c00b538:	5692                	lw	a3,36(sp)
1c00b53a:	5722                	lw	a4,40(sp)
1c00b53c:	57b2                	lw	a5,44(sp)
1c00b53e:	5842                	lw	a6,48(sp)
1c00b540:	58d2                	lw	a7,52(sp)
1c00b542:	5e62                	lw	t3,56(sp)
1c00b544:	5ef2                	lw	t4,60(sp)
1c00b546:	4f06                	lw	t5,64(sp)
1c00b548:	4fb6                	lw	t6,76(sp)
1c00b54a:	6109                	addi	sp,sp,128
1c00b54c:	8482                	jr	s1

1c00b54e <pos_irq_call_external_c_function_full>:
1c00b54e:	7119                	addi	sp,sp,-128
1c00b550:	c006                	sw	ra,0(sp)
1c00b552:	c20e                	sw	gp,4(sp)
1c00b554:	c412                	sw	tp,8(sp)
1c00b556:	c616                	sw	t0,12(sp)
1c00b558:	c81a                	sw	t1,16(sp)
1c00b55a:	ca1e                	sw	t2,20(sp)
1c00b55c:	cc2a                	sw	a0,24(sp)
1c00b55e:	ce2e                	sw	a1,28(sp)
1c00b560:	d236                	sw	a3,36(sp)
1c00b562:	d43a                	sw	a4,40(sp)
1c00b564:	d63e                	sw	a5,44(sp)
1c00b566:	d842                	sw	a6,48(sp)
1c00b568:	da46                	sw	a7,52(sp)
1c00b56a:	dc72                	sw	t3,56(sp)
1c00b56c:	de76                	sw	t4,60(sp)
1c00b56e:	c0fa                	sw	t5,64(sp)
1c00b570:	c6fe                	sw	t6,76(sp)
1c00b572:	000600e7          	jalr	a2
1c00b576:	4082                	lw	ra,0(sp)
1c00b578:	4192                	lw	gp,4(sp)
1c00b57a:	4222                	lw	tp,8(sp)
1c00b57c:	42b2                	lw	t0,12(sp)
1c00b57e:	4342                	lw	t1,16(sp)
1c00b580:	43d2                	lw	t2,20(sp)
1c00b582:	4562                	lw	a0,24(sp)
1c00b584:	45f2                	lw	a1,28(sp)
1c00b586:	5692                	lw	a3,36(sp)
1c00b588:	5722                	lw	a4,40(sp)
1c00b58a:	57b2                	lw	a5,44(sp)
1c00b58c:	5842                	lw	a6,48(sp)
1c00b58e:	58d2                	lw	a7,52(sp)
1c00b590:	5e62                	lw	t3,56(sp)
1c00b592:	5ef2                	lw	t4,60(sp)
1c00b594:	4f06                	lw	t5,64(sp)
1c00b596:	4fb6                	lw	t6,76(sp)
1c00b598:	6109                	addi	sp,sp,128
1c00b59a:	8482                	jr	s1

1c00b59c <pos_task_push_asm>:
1c00b59c:	e3ff5297          	auipc	t0,0xe3ff5
1c00b5a0:	a8428293          	addi	t0,t0,-1404 # 20 <pos_sched_first>
1c00b5a4:	0002a603          	lw	a2,0(t0)
1c00b5a8:	0005a023          	sw	zero,0(a1)
1c00b5ac:	ca09                	beqz	a2,1c00b5be <__rt_no_first>
1c00b5ae:	e3ff5297          	auipc	t0,0xe3ff5
1c00b5b2:	a7628293          	addi	t0,t0,-1418 # 24 <pos_sched_last>
1c00b5b6:	0002a603          	lw	a2,0(t0)
1c00b5ba:	c20c                	sw	a1,0(a2)
1c00b5bc:	a029                	j	1c00b5c6 <__rt_common>

1c00b5be <__rt_no_first>:
1c00b5be:	e3ff5297          	auipc	t0,0xe3ff5
1c00b5c2:	a6b2a123          	sw	a1,-1438(t0) # 20 <pos_sched_first>

1c00b5c6 <__rt_common>:
1c00b5c6:	e3ff5297          	auipc	t0,0xe3ff5
1c00b5ca:	a4b2af23          	sw	a1,-1442(t0) # 24 <pos_sched_last>

1c00b5ce <enqueue_end>:
1c00b5ce:	8482                	jr	s1

1c00b5d0 <pos_task_remote_enqueue>:
1c00b5d0:	fe812e23          	sw	s0,-4(sp)
1c00b5d4:	fe912c23          	sw	s1,-8(sp)
1c00b5d8:	fea12a23          	sw	a0,-12(sp)
1c00b5dc:	feb12823          	sw	a1,-16(sp)
1c00b5e0:	fec12623          	sw	a2,-20(sp)
1c00b5e4:	fe512423          	sw	t0,-24(sp)
1c00b5e8:	4405                	li	s0,1
1c00b5ea:	ffffc497          	auipc	s1,0xffffc
1c00b5ee:	e4648493          	addi	s1,s1,-442 # 1c007430 <pos_cluster>

1c00b5f2 <pos_task_remote_enqueue_event_loop_cluster>:
1c00b5f2:	48cc                	lw	a1,20(s1)
1c00b5f4:	40d0                	lw	a2,4(s1)
1c00b5f6:	02058a63          	beqz	a1,1c00b62a <pos_task_remote_enqueue_event_loop_cluster_continue>
1c00b5fa:	4208                	lw	a0,0(a2)
1c00b5fc:	e119                	bnez	a0,1c00b602 <pos_task_remote_enqueue_no_queue_update>
1c00b5fe:	0004a023          	sw	zero,0(s1)

1c00b602 <pos_task_remote_enqueue_no_queue_update>:
1c00b602:	4890                	lw	a2,16(s1)
1c00b604:	0004aa23          	sw	zero,20(s1)
1c00b608:	00062023          	sw	zero,0(a2)
1c00b60c:	00000497          	auipc	s1,0x0
1c00b610:	01e48493          	addi	s1,s1,30 # 1c00b62a <pos_task_remote_enqueue_event_loop_cluster_continue>
1c00b614:	0035f513          	andi	a0,a1,3
1c00b618:	00051363          	bnez	a0,1c00b61e <pos_task_callback>
1c00b61c:	b741                	j	1c00b59c <pos_task_push_asm>

1c00b61e <pos_task_callback>:
1c00b61e:	5571                	li	a0,-4
1c00b620:	8de9                	and	a1,a1,a0
1c00b622:	41d0                	lw	a2,4(a1)
1c00b624:	4588                	lw	a0,8(a1)
1c00b626:	ee3ff06f          	j	1c00b508 <pos_irq_call_external_c_function>

1c00b62a <pos_task_remote_enqueue_event_loop_cluster_continue>:
1c00b62a:	147d                	addi	s0,s0,-1
1c00b62c:	02804063          	bgtz	s0,1c00b64c <pos_task_remote_enqueue_event_loop_next_cluster>
1c00b630:	ffc12403          	lw	s0,-4(sp)
1c00b634:	ff812483          	lw	s1,-8(sp)
1c00b638:	ff412503          	lw	a0,-12(sp)
1c00b63c:	ff012583          	lw	a1,-16(sp)
1c00b640:	fec12603          	lw	a2,-20(sp)
1c00b644:	fe812283          	lw	t0,-24(sp)
1c00b648:	30200073          	mret

1c00b64c <pos_task_remote_enqueue_event_loop_next_cluster>:
1c00b64c:	ffffc497          	auipc	s1,0xffffc
1c00b650:	de448493          	addi	s1,s1,-540 # 1c007430 <pos_cluster>
1c00b654:	02c00593          	li	a1,44
1c00b658:	02b405b3          	mul	a1,s0,a1
1c00b65c:	94ae                	add	s1,s1,a1
1c00b65e:	bf51                	j	1c00b5f2 <pos_task_remote_enqueue_event_loop_cluster>

1c00b660 <pos_time_timer_handler_asm>:
1c00b660:	1161                	addi	sp,sp,-8
1c00b662:	c032                	sw	a2,0(sp)
1c00b664:	c226                	sw	s1,4(sp)
1c00b666:	00000617          	auipc	a2,0x0
1c00b66a:	a4a60613          	addi	a2,a2,-1462 # 1c00b0b0 <pos_time_timer_handler>
1c00b66e:	00000497          	auipc	s1,0x0
1c00b672:	00c48493          	addi	s1,s1,12 # 1c00b67a <pos_time_timer_handler_asm_ret>
1c00b676:	ed9ff06f          	j	1c00b54e <pos_irq_call_external_c_function_full>

1c00b67a <pos_time_timer_handler_asm_ret>:
1c00b67a:	4492                	lw	s1,4(sp)
1c00b67c:	4602                	lw	a2,0(sp)
1c00b67e:	0121                	addi	sp,sp,8
1c00b680:	30200073          	mret

1c00b684 <pos_soc_event_handler_asm>:
1c00b684:	7119                	addi	sp,sp,-128
1c00b686:	c022                	sw	s0,0(sp)
1c00b688:	c226                	sw	s1,4(sp)
1c00b68a:	c42a                	sw	a0,8(sp)
1c00b68c:	c62e                	sw	a1,12(sp)
1c00b68e:	c832                	sw	a2,16(sp)
1c00b690:	ca16                	sw	t0,20(sp)
1c00b692:	1a10a437          	lui	s0,0x1a10a
1c00b696:	80040413          	addi	s0,s0,-2048 # 1a109800 <__l1_end+0xa1097d0>
1c00b69a:	5048                	lw	a0,36(s0)
1c00b69c:	00251593          	slli	a1,a0,0x2
1c00b6a0:	e3ff5297          	auipc	t0,0xe3ff5
1c00b6a4:	da828293          	addi	t0,t0,-600 # 448 <pos_soc_event_callback>
1c00b6a8:	2055f603          	p.lw	a2,t0(a1)
1c00b6ac:	e3ff5297          	auipc	t0,0xe3ff5
1c00b6b0:	99c28293          	addi	t0,t0,-1636 # 48 <pos_soc_event_callback_arg>
1c00b6b4:	2055f583          	p.lw	a1,t0(a1)
1c00b6b8:	00000497          	auipc	s1,0x0
1c00b6bc:	03048493          	addi	s1,s1,48 # 1c00b6e8 <pos_soc_event_handler_end_asm>
1c00b6c0:	e49ff06f          	j	1c00b508 <pos_irq_call_external_c_function>

1c00b6c4 <pos_soc_event_no_udma_asm>:
1c00b6c4:	00555593          	srli	a1,a0,0x5
1c00b6c8:	058a                	slli	a1,a1,0x2
1c00b6ca:	e3ff5297          	auipc	t0,0xe3ff5
1c00b6ce:	95e28293          	addi	t0,t0,-1698 # 28 <pos_soc_event_status>
1c00b6d2:	2055f603          	p.lw	a2,t0(a1)
1c00b6d6:	897d                	andi	a0,a0,31
1c00b6d8:	80a64633          	p.bsetr	a2,a2,a0
1c00b6dc:	e3ff5297          	auipc	t0,0xe3ff5
1c00b6e0:	94c28293          	addi	t0,t0,-1716 # 28 <pos_soc_event_status>
1c00b6e4:	00c5e2a3          	p.sw	a2,t0(a1)

1c00b6e8 <pos_soc_event_handler_end_asm>:
1c00b6e8:	4402                	lw	s0,0(sp)
1c00b6ea:	4492                	lw	s1,4(sp)
1c00b6ec:	4522                	lw	a0,8(sp)
1c00b6ee:	45b2                	lw	a1,12(sp)
1c00b6f0:	4642                	lw	a2,16(sp)
1c00b6f2:	42d2                	lw	t0,20(sp)
1c00b6f4:	6109                	addi	sp,sp,128
1c00b6f6:	30200073          	mret

1c00b6fa <_endtext>:
	...

Disassembly of section .l2_data:

1c010000 <__cluster_text_start>:
1c010000:	f1402573          	csrr	a0,mhartid
1c010004:	01f57593          	andi	a1,a0,31
1c010008:	8115                	srli	a0,a0,0x5
1c01000a:	000702b7          	lui	t0,0x70
1c01000e:	00204337          	lui	t1,0x204
1c010012:	00532023          	sw	t0,0(t1) # 204000 <__l1_heap_size+0x1f4030>
1c010016:	4381                	li	t2,0
1c010018:	0e759463          	bne	a1,t2,1c010100 <pos_slave_start>
1c01001c:	20000293          	li	t0,512
1c010020:	00204337          	lui	t1,0x204
1c010024:	00532a23          	sw	t0,20(t1) # 204014 <__l1_heap_size+0x1f4044>
1c010028:	e3ff0417          	auipc	s0,0xe3ff0
1c01002c:	fdc40413          	addi	s0,s0,-36 # 4 <pos_fll_freq>
1c010030:	002049b7          	lui	s3,0x204
1c010034:	4a09                	li	s4,2
1c010036:	00000a97          	auipc	s5,0x0
1c01003a:	038a8a93          	addi	s5,s5,56 # 1c01006e <pos_master_event>
1c01003e:	ffff7b97          	auipc	s7,0xffff7
1c010042:	3f2b8b93          	addi	s7,s7,1010 # 1c007430 <pos_cluster>
1c010046:	02c00393          	li	t2,44
1c01004a:	02a383b3          	mul	t2,t2,a0
1c01004e:	9b9e                	add	s7,s7,t2
1c010050:	0bd1                	addi	s7,s7,20
1c010052:	1a10acb7          	lui	s9,0x1a10a
1c010056:	810c8c93          	addi	s9,s9,-2032 # 1a109810 <__l1_end+0xa1097e0>
1c01005a:	4c09                	li	s8,2
1c01005c:	00000d17          	auipc	s10,0x0
1c010060:	0e2d0d13          	addi	s10,s10,226 # 1c01013e <pos_set_slave_stack>
1c010064:	001d6d13          	ori	s10,s10,1
1c010068:	30045073          	csrwi	mstatus,8
1c01006c:	a829                	j	1c010086 <pos_master_loop>

1c01006e <pos_master_event>:
1c01006e:	018b2b03          	lw	s6,24(s6)
1c010072:	000b0a63          	beqz	s6,1c010086 <pos_master_loop>

1c010076 <pos_push_event_to_fc_retry>:
1c010076:	000ba283          	lw	t0,0(s7)
1c01007a:	06029c63          	bnez	t0,1c0100f2 <pos_push_event_to_fc_wait>
1c01007e:	016ba023          	sw	s6,0(s7)
1c010082:	018ca023          	sw	s8,0(s9)

1c010086 <pos_master_loop>:
1c010086:	00042b03          	lw	s6,0(s0)
1c01008a:	040b0d63          	beqz	s6,1c0100e4 <pos_master_sleep>

1c01008e <pos_master_loop_update_next>:
1c01008e:	020b2e83          	lw	t4,32(s6)
1c010092:	01d42023          	sw	t4,0(s0)
1c010096:	020b2f03          	lw	t5,32(s6)
1c01009a:	ffee9ae3          	bne	t4,t5,1c01008e <pos_master_loop_update_next>

1c01009e <pos_master_loop_exec_task>:
1c01009e:	004b2503          	lw	a0,4(s6)
1c0100a2:	000b2283          	lw	t0,0(s6)
1c0100a6:	008b2103          	lw	sp,8(s6)
1c0100aa:	00cb2303          	lw	t1,12(s6)
1c0100ae:	010b2383          	lw	t2,16(s6)
1c0100b2:	024b2f03          	lw	t5,36(s6)
1c0100b6:	014b2f83          	lw	t6,20(s6)
1c0100ba:	80d6                	mv	ra,s5
1c0100bc:	911a                	add	sp,sp,t1
1c0100be:	e3ff0e17          	auipc	t3,0xe3ff0
1c0100c2:	f5fe2d23          	sw	t6,-166(t3) # 18 <pos_cluster_nb_active_pe>

1c0100c6 <pos_no_stack_check>:
1c0100c6:	09e9a223          	sw	t5,132(s3) # 204084 <__l1_heap_size+0x1f40b4>
1c0100ca:	21e9a023          	sw	t5,512(s3)
1c0100ce:	21e9a623          	sw	t5,524(s3)

1c0100d2 <pos_master_no_slave_barrier>:
1c0100d2:	000f2863          	p.beqimm	t5,0,1c0100e2 <pos_master_loop_no_slave>
1c0100d6:	09a9a023          	sw	s10,128(s3)
1c0100da:	0879a023          	sw	t2,128(s3)
1c0100de:	0829a023          	sw	sp,128(s3)

1c0100e2 <pos_master_loop_no_slave>:
1c0100e2:	8282                	jr	t0

1c0100e4 <pos_master_sleep>:
1c0100e4:	0149a423          	sw	s4,8(s3)
1c0100e8:	03c9e003          	p.elw	zero,60(s3)
1c0100ec:	0149a223          	sw	s4,4(s3)
1c0100f0:	bf59                	j	1c010086 <pos_master_loop>

1c0100f2 <pos_push_event_to_fc_wait>:
1c0100f2:	0149a423          	sw	s4,8(s3)
1c0100f6:	03c9e003          	p.elw	zero,60(s3)
1c0100fa:	0149a223          	sw	s4,4(s3)
1c0100fe:	bfa5                	j	1c010076 <pos_push_event_to_fc_retry>

1c010100 <pos_slave_start>:
1c010100:	00204937          	lui	s2,0x204
1c010104:	f14029f3          	csrr	s3,mhartid
1c010108:	01f9f993          	andi	s3,s3,31
1c01010c:	00000a17          	auipc	s4,0x0
1c010110:	012a0a13          	addi	s4,s4,18 # 1c01011e <pos_fork_return>
1c010114:	00000a97          	auipc	s5,0x0
1c010118:	00ea8a93          	addi	s5,s5,14 # 1c010122 <pos_wait_for_dispatch>
1c01011c:	a019                	j	1c010122 <pos_wait_for_dispatch>

1c01011e <pos_fork_return>:
1c01011e:	21c96283          	p.elw	t0,540(s2) # 20421c <__l1_heap_size+0x1f424c>

1c010122 <pos_wait_for_dispatch>:
1c010122:	08096283          	p.elw	t0,128(s2)
1c010126:	08096503          	p.elw	a0,128(s2)
1c01012a:	0012f313          	andi	t1,t0,1
1c01012e:	00031563          	bnez	t1,1c010138 <pos_other_entry>

1c010132 <pos_fork_entry>:
1c010132:	000a00b3          	add	ra,s4,zero
1c010136:	8282                	jr	t0

1c010138 <pos_other_entry>:
1c010138:	000a80b3          	add	ra,s5,zero
1c01013c:	8282                	jr	t0

1c01013e <pos_set_slave_stack>:
1c01013e:	08096283          	p.elw	t0,128(s2)
1c010142:	00098f13          	mv	t5,s3
1c010146:	02af0eb3          	mul	t4,t5,a0
1c01014a:	005e8133          	add	sp,t4,t0
1c01014e:	8082                	ret

1c010150 <__cluster_text_end>:
	...
