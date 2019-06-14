################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uC-LIB/lib_ascii.obj: ../uC-LIB/lib_ascii.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-LIB/lib_ascii.d_raw" --obj_directory="uC-LIB" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uC-LIB/lib_math.obj: ../uC-LIB/lib_math.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-LIB/lib_math.d_raw" --obj_directory="uC-LIB" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uC-LIB/lib_mem.obj: ../uC-LIB/lib_mem.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-LIB/lib_mem.d_raw" --obj_directory="uC-LIB" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uC-LIB/lib_str.obj: ../uC-LIB/lib_str.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-LIB/lib_str.d_raw" --obj_directory="uC-LIB" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


