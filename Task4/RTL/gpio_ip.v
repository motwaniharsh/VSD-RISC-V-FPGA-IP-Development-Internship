module gpio_ip(
    input clk,
    input we,
    input [31:0] wdata,
    output [31:0] rdata,
    output [31:0] gpio_out
);

reg [31:0] gpio_reg;

always @(posedge clk) begin
    if(we)
        gpio_reg <= wdata;
end

assign rdata = gpio_reg;
assign gpio_out = gpio_reg;

endmodule
