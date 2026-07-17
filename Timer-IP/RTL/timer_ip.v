module timer_ip(
    input clk,
    input reset,
    input we,
    input [3:0] addr,
    input [31:0] wdata,

    output reg [31:0] rdata,
    output timeout
);

reg [31:0] ctrl_reg;      // Control register
reg [31:0] load_reg;      // Load value
reg [31:0] value_reg;     // Current countdown value

reg timeout_flag;         // Timeout status bit

reg [15:0] prescaler_cnt; // Prescaler counter

wire en;
wire mode;
wire presc_en;

wire [7:0] presc_div;

assign en = ctrl_reg[0];
assign mode = ctrl_reg[1];
assign presc_en = ctrl_reg[2];

assign presc_div = ctrl_reg[15:8];

assign timeout = timeout_flag;

//register write logic
always @(posedge clk) begin

    if(reset) begin

        ctrl_reg <= 0;
        load_reg <= 0;
        value_reg <= 0;

        timeout_flag <= 0;

        prescaler_cnt <= 0;

    end

    else if(we) begin

        case(addr)

            4'h0:
                ctrl_reg <= wdata;

            4'h4:
                load_reg <= wdata;

            4'hC:
                if(wdata[0])
                    timeout_flag <= 0;
            
            default:
            	;

        endcase

    end
    
    else begin

		if(en) begin

		    // Initial load
		    if(value_reg == 0 && !timeout_flag) begin

		        value_reg <= load_reg;

		    end

		    else begin

		        // Prescaler disabled
		        if(!presc_en) begin

		            if(value_reg > 0) begin

		                value_reg <= value_reg - 1;

		                if(value_reg == 1) begin

		                    timeout_flag <= 1'b1;

		                    // Periodic mode
		                    if(mode)
		                        value_reg <= load_reg;
		                end

		            end

		        end

		        // Prescaler enabled
		        else begin

		            if(prescaler_cnt == presc_div) begin

		                prescaler_cnt <= 0;

		                if(value_reg > 0) begin

		                    value_reg <= value_reg - 1;

		                    if(value_reg == 1) begin

		                        timeout_flag <= 1'b1;

		                        if(mode)
		                            value_reg <= load_reg;
		                    end

		                end

		            end

		            else begin

		                prescaler_cnt <= prescaler_cnt + 1;
		            end

		        end

		    end

		end

	end

end

//register read logic
always @(*) begin

    case(addr)

        4'h0:
            rdata = ctrl_reg;

        4'h4:
            rdata = load_reg;

        4'h8:
            rdata = value_reg;

        4'hC:
            rdata = {31'b0, timeout_flag};

        default:
            rdata = 32'b0;

    endcase

end

endmodule
