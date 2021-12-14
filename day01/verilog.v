module partTwo(input clk, input rst, input [31:0] inp, output reg [31:0] out);

reg [3:0] measurements;
reg [31:0] sliceOne;
reg [31:0] sliceTwo;
reg [31:0] sliceThree;

always @ (posedge clk, posedge rst) begin
	if (rst) begin  // reset
		out <= 0;
		measurements <= 0;
	end else if (measurements == 3 
		&& sliceOne + sliceTwo + sliceThree < sliceTwo + sliceThree + inp) begin
			out <= out + 1;
		end

	// Save measurements
	if (!rst) begin
		// Shift measurements
		sliceOne <= sliceTwo;
		sliceTwo <= sliceThree;
		sliceThree <= inp;

		if(measurements < 3) measurements <= measurements + 1;  // increase measurements if nec.
	end
end

endmodule


// first part of the challenge
module partOne(input clk, input rst, input [31:0] inp, output reg [31:0] out);

reg first;
reg [31:0] last;
reg [31:0] counter;

always @ (posedge clk, posedge rst) begin
	if (rst) begin
		first <= 1'b1;
		counter <= 0;
	end else begin
		if (first) begin  // first input
			first <= 1'b0;
		end else if (inp > last) begin  // check if is bigger
			counter <= counter + 1;
		end

		last <= inp;
	end
end

// move counter to output register
always @ (counter) begin
	out = counter;
end

endmodule
