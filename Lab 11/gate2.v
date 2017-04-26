//Bryce Monaco, Alex Kastanek
//CPE 301 - Lab 11 - Question 2
//Version 1.0

module gate2 (in_a, in_b, out);

input wire in_a;	// declare input variable in_a
input wire in_b;	// declare input variable in_b
output wire [5:0] out;	// output variables, mapped to LEDs above switches

assign out[5] = in_a & in_b;
assign out[4] = ~(in_a & in_b);
assign out[3] = in_a | in_b;
assign out[2] = ~(in_a | in_b);
assign out[1] = in_a ^ in_b;
assign out[0] = ~(in_a ^ in_b);

endmodule

//Note: Originally out[1]’s assignment didn’t work, not because of the
//..code but because the tutorial maps it to the incorrect output