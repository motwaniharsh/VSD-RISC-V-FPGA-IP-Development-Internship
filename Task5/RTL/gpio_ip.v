module gpio_ip(
    input             clk,
    input             we,
    input      [3:0]  addr,
    input      [31:0] wdata,
    output reg [31:0] rdata,
    output     [31:0] gpio_out
);

    // Internal Registers
    reg [31:0] gpio_data;
    reg [31:0] gpio_dir;

    // GPIO Output Logic
    // Only pins configured as outputs drive values
    assign gpio_out = gpio_data & gpio_dir;

    // Write Logic
    always @(posedge clk) begin
        if (we) begin
            case (addr)
                4'h0: gpio_data <= wdata;   // GPIO_DATA
                4'h4: gpio_dir  <= wdata;   // GPIO_DIR
                default: ;
            endcase
        end
    end

    // Read Logic
    always @(*) begin
        case (addr)
            4'h0: rdata = gpio_data;     // GPIO_DATA
            4'h4: rdata = gpio_dir;      // GPIO_DIR
            4'h8: rdata = gpio_out;      // GPIO_READ
            default: rdata = 32'b0;
        endcase
    end

endmodule