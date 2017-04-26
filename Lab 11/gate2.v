module gate2 (in_a, in_b, out);

input wire in_a;	// declare input variable in_a
input wire in_b;
output wire [5:0] out;

assign out[5] = in_a & in_b;
assign out[4] = ~(in_a & in_b);
assign out[3] = in_a | in_b;
assign out[2] = ~(in_a | in_b);
assign out[1] = in_a ^ in_b;
assign out[0] = ~(in_a ^ in_b);

endmodule