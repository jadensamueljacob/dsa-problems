module shift_register (
    input clk,             // Clock signal
    input reset,           // Reset signal
    input serial_in,       // Serial input
    output reg serial_out, // Serial output
    output reg [3:0] parallel_out // Parallel output
);
    reg [3:0] shift_reg;   // Internal 4-bit shift register

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            shift_reg <= 4'b0000;
            serial_out <= 0;
            parallel_out <= 4'b0000; // Reset parallel output
        end else begin
            serial_out <= shift_reg[3]; // Serial output is MSB
            shift_reg <= {shift_reg[2:0], serial_in}; // Shift left
            parallel_out <= shift_reg;  // Update parallel output with new value
        end
    end
endmodule
