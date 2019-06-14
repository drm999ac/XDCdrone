################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
uCOS-II/Source/os_core.obj: ../uCOS-II/Source/os_core.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_core.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_flag.obj: ../uCOS-II/Source/os_flag.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_flag.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_mbox.obj: ../uCOS-II/Source/os_mbox.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_mbox.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_mem.obj: ../uCOS-II/Source/os_mem.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_mem.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_mutex.obj: ../uCOS-II/Source/os_mutex.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_mutex.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_q.obj: ../uCOS-II/Source/os_q.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_q.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_sem.obj: ../uCOS-II/Source/os_sem.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_sem.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_task.obj: ../uCOS-II/Source/os_task.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_task.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_time.obj: ../uCOS-II/Source/os_time.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_time.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uCOS-II/Source/os_tmr.obj: ../uCOS-II/Source/os_tmr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="uCOS-II/Source/os_tmr.d_raw" --obj_directory="uCOS-II/Source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


