################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uCOS-II/Ports/C28x/Generic/CCS/os_cpu_a.obj: ../uCOS-II/Ports/C28x/Generic/CCS/os_cpu_a.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/os_cpu_a.d_raw" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Ports/C28x/Generic/CCS/os_cpu_c.obj: ../uCOS-II/Ports/C28x/Generic/CCS/os_cpu_c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/os_cpu_c.d_raw" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Ports/C28x/Generic/CCS/os_cpu_i.obj: ../uCOS-II/Ports/C28x/Generic/CCS/os_cpu_i.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/os_cpu_i.d_raw" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Ports/C28x/Generic/CCS/os_dbg.obj: ../uCOS-II/Ports/C28x/Generic/CCS/os_dbg.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Ports/C28x/Generic/CCS/os_dbg.d_raw" --obj_directory="uCOS-II/Ports/C28x/Generic/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


