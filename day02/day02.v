module partTwo(input clk, input rst, input [1:0] cmd, input [31:0] distance , output reg [31:0] out);

localparam FORWARD = 2'd0, UP = 2'd1, DOWN = 2'd2;

reg [31:0] horizontal;
reg [31:0] depth;
reg [31:0] aim;

always @ (posedge clk, posedge rst) begin
	if (rst) begin  // reset
		horizontal <= 0;
		depth <= 0;
		aim <= 0;
	end else begin
		case (cmd)
			FORWARD: begin
				horizontal <= horizontal + distance;
				depth <= depth + aim * distance;
			end
			UP: aim <= aim - distance;
			DOWN: aim <= aim + distance;
			default: $stop;
		endcase
	end
end

always @ (horizontal, depth) out = horizontal * depth;

endmodule




module partOne(input clk, input rst, input [1:0] cmd, input [31:0] distance , output reg [31:0] out);

localparam FORWARD = 2'd0, UP = 2'd1, DOWN = 2'd2;

reg [31:0] horizontal;
reg [31:0] depth;

always @ (posedge clk, posedge rst) begin
	if (rst) begin  // reset
		horizontal <= 0;
		depth <= 0;
	end else begin
		case (cmd)
			FORWARD: horizontal <= horizontal + distance;
			UP: depth <= depth - distance;
			DOWN: depth <= depth + distance;
			default: $stop;
		endcase
	end
end

always @ (horizontal, depth) out = horizontal * depth;

endmodule
