//Bryce Monaco, Alex Kastanek
//CPE 301 - Lab 11 - Question 3
//Version 1.0

module number3 (in_a, in_b, in_en, out, segOut);

//Input Variables
input wire in_a;	
input wire in_b;
input wire in_en;

//Output Variables
output wire [4:0] out;		//Set of LEDs above switches (2to4 debug)
output wire [6:0] segOut;	//7 set display HEX0

//2 to 4 Decoder, outputs to LEDs for debug
assign out[3] = in_a & in_b & in_en;
assign out[2] = ~in_a & in_b & in_en;
assign out[1] = in_a & ~in_b & in_en;
assign out[0] = ~in_a & ~in_b & in_en;

//Uses the decoder output to decide which segments to enable
//..note segments are active low, so writing a 1 turns them off
assign segOut[6] = ~in_en | out[0];
assign segOut[5] = out[0] | out[1] | out[2];
assign segOut[4] = out[0] | out[2] | out[3];
assign segOut[3] = out[0] | out[3];
assign segOut[2] = out[1];
assign segOut[1] = 0;
assign segOut[0] = out[0] | out[3];

endmodule