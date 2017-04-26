module number3 (in_a, in_b, in_en, out, segOut);

input wire in_a;	// declare input variable in_a
input wire in_b;
input wire in_en;
output wire [4:0] out;
output wire [6:0] segOut;

assign out[3] = in_a & in_b & in_en;
assign out[2] = ~in_a & in_b & in_en;
assign out[1] = in_a & ~in_b & in_en;
assign out[0] = ~in_a & ~in_b & in_en;

assign segOut[6] = ~in_en | out[0];
assign segOut[5] = out[0] | out[1] | out[2];
assign segOut[4] = out[0] | out[2] | out[3];
assign segOut[3] = out[0] | out[3];
assign segOut[2] = out[1];
assign segOut[1] = 0;
assign segOut[0] = out[0] | out[3];

endmodule