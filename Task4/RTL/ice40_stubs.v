module SB_HFOSC
#(
    parameter CLKHF_DIV = "0b10"
)
(
    input CLKHFPU,
    input CLKHFEN,
    output CLKHF
);

    reg clk = 0;

    always #5 clk = ~clk;

    assign CLKHF = clk;

endmodule


module SB_PLL40_CORE
#(
    parameter FEEDBACK_PATH = "SIMPLE",
    parameter PLLOUT_SELECT = "GENCLK",
    parameter DIVR = 4'b0000,
    parameter DIVF = 7'b0000000,
    parameter DIVQ = 3'b000,
    parameter FILTER_RANGE = 3'b000
)
(
    input REFERENCECLK,
    input RESETB,
    input BYPASS,
    output PLLOUTCORE
);

    assign PLLOUTCORE = REFERENCECLK;

endmodule