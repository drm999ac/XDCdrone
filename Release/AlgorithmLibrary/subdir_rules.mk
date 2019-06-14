################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
AlgorithmLibrary/Calibrate.obj: ../AlgorithmLibrary/Calibrate.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="AlgorithmLibrary/Calibrate.d_raw" --obj_directory="AlgorithmLibrary" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

AlgorithmLibrary/MahonyAHRS.obj: ../AlgorithmLibrary/MahonyAHRS.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="AlgorithmLibrary/MahonyAHRS.d_raw" --obj_directory="AlgorithmLibrary" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

AlgorithmLibrary/PositionEstimation.obj: ../AlgorithmLibrary/PositionEstimation.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="AlgorithmLibrary/PositionEstimation.d_raw" --obj_directory="AlgorithmLibrary" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

AlgorithmLibrary/SimpleDigitalFiltering.obj: ../AlgorithmLibrary/SimpleDigitalFiltering.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt -O2 --include_path="F:/project/ti/C2000/BirdFlight_V3.0.5" --include_path="D:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="AlgorithmLibrary/SimpleDigitalFiltering.d_raw" --obj_directory="AlgorithmLibrary" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


