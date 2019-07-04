################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FLASH_API/%.obj: ../FLASH_API/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="H:/project/ti/BridFlight_V3.0.5" --include_path="F:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="FLASH_API/$(basename $(<F)).d_raw" --obj_directory="FLASH_API" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


