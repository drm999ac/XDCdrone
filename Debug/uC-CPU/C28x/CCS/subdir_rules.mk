################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uC-CPU/C28x/CCS/cpu_a.obj: ../uC-CPU/C28x/CCS/cpu_a.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -Ooff --opt_for_speed=0 --fp_mode=relaxed --fp_reassoc=on --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/FLASH_API" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/FLASH_API/include" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/FLASH_API/include/Constants" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Control" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/FLASH_API/src" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Parameter" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Sensor" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/HardWare" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uC-CPU" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uC-CPU/C28x/CCS" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uC-LIB" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uCOS-CORE" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/AlgorithmLibrary" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uCOS-II/Ports/C28x/Generic/CCS" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uCOS-II/Source" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Driver/include/include1" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Driver/include/include2" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-CPU/C28x/CCS/cpu_a.d_raw" --obj_directory="uC-CPU/C28x/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uC-CPU/C28x/CCS/cpu_c.obj: ../uC-CPU/C28x/CCS/cpu_c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -Ooff --opt_for_speed=0 --fp_mode=relaxed --fp_reassoc=on --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/FLASH_API" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/FLASH_API/include" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/FLASH_API/include/Constants" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Control" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/FLASH_API/src" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Parameter" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Sensor" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/HardWare" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uC-CPU" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uC-CPU/C28x/CCS" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uC-LIB" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uCOS-CORE" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/AlgorithmLibrary" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uCOS-II/Ports/C28x/Generic/CCS" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/uCOS-II/Source" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Driver/include/include1" --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5/Driver/include/include2" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --advice:performance=all -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uC-CPU/C28x/CCS/cpu_c.d_raw" --obj_directory="uC-CPU/C28x/CCS" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


