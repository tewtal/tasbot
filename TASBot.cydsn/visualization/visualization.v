//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 12/06/2016 at 19:05
// Component: visualization
module visualization (
	output  clock,
	output  d0,
	output  d1,
	output  d2,
	output  d3,
	output  reg latch,
	input   clk,
	input  [7:0] input0_h,
	input  [7:0] input0_l,
	input  [7:0] input1_h,
	input  [7:0] input1_l,
	input  [7:0] input2_h,
	input  [7:0] input2_l,
	input  [7:0] input3_h,
	input  [7:0] input3_l
);

//`#start body` -- edit after this line, do not edit this line
    reg [15:0] latched_data0;
    reg [15:0] latched_data1;
    reg [15:0] latched_data2;
    reg [15:0] latched_data3;

    reg [2:0] state;
    reg [3:0] pos;
    
    reg clock_1;
    reg clock_2;
   
    assign clock = (state == 1) ? ~clk : 1'b0;
    assign d0 = latched_data0[pos];
    assign d1 = latched_data1[pos];
    assign d2 = latched_data2[pos];
    assign d3 = latched_data3[pos];
    
    always @ (posedge clk)
    begin
        case(state)
            0:
                begin
                    latched_data0[15:8] <= input0_h;
                    latched_data0[7:0] <= input0_l;
                    latched_data1[15:8] <= input1_h;
                    latched_data1[7:0] <= input1_l;
                    latched_data2[15:8] <= input2_h;
                    latched_data2[7:0] <= input2_l;
                    latched_data3[15:8] <= input3_h;
                    latched_data3[7:0] <= input3_l;
                    state <= 1;
                end
            1:
                begin
                    if(pos == 0)
                    begin
                        pos <= 15;
                        state <= 2;
                    end
                    else
                    begin
                        pos <= pos - 1;
                    end
                end
            2:
                begin
                    latch <= 1;
                    state <= 3;
                end
            3:
                begin
                    latch <= 0;
                    state <= 0;
                end
        endcase                
    end

    initial begin
        state <= 0;
        pos <= 15;
        latched_data0 <= 0;
        latched_data1 <= 0;
        latched_data2 <= 0;
        latched_data3 <= 0;
    end

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line

//`#end` -- edit above this line, do not edit this line
