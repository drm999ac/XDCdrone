################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uCOS-II/Ports/C28x/Generic/CCS/%.obj: ../uCOS-II/Ports/C28x/Generic/CCS/%.asm $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="H:/project/ti/BridFlight_V3.0.5" --include_path="F:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/$(basename $(<F)).d_raw" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Ports/C28x/Generic/CCS/%.obj: ../uCOS-II/Ports/C28x/Generic/CCS/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"F:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="H:/project/ti/BridFlight_V3.0.5" --include_path="F:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/$(basename $(<F)).d_raw" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


