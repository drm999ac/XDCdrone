################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
HardWare/C28x_BSP.obj: ../HardWare/C28x_BSP.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="HardWare/C28x_BSP.d_raw" --obj_directory="HardWare" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

HardWare/C28x_CPU.obj: ../HardWare/C28x_CPU.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="HardWare/C28x_CPU.d_raw" --obj_directory="HardWare" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


