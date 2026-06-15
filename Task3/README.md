# Task 3: Environment Setup & RISC-V Reference Bring-Up

## Objective

The objective of this task is to establish a functional RISC-V development environment using GitHub Codespaces and verify that the provided reference environment is correctly configured. This environment will serve as the foundation for subsequent RISC-V, IP integration, and FPGA development tasks.

---

## Introduction

Before developing custom IP blocks or working with FPGA hardware, it is essential to verify that the software development environment is functioning correctly. The official `vsd-riscv2` repository provides a preconfigured development environment containing the required tools and dependencies for RISC-V development.

In this task, the GitHub Codespace environment provided by the repository is launched and verified to ensure that all required components are available and functioning correctly.

---

## Environment Used

- GitHub Codespaces
- Ubuntu Linux Environment
- VS Code Web Interface
- Preconfigured RISC-V Toolchain
- Official `vsd-riscv2` Repository

---

## Repository Used

```bash
https://github.com/vsdip/vsd-riscv2
```

---

# Step 1: GitHub Codespace Setup

## Accessing the Repository

The official `vsd-riscv2` repository was opened on GitHub. The repository contains a preconfigured development environment with the required RISC-V tools, libraries, and supporting infrastructure needed for the internship tasks.

### Screenshot

![Repository Access](sreenshots/repository_access.png)

---

## Launching GitHub Codespace

A new GitHub Codespace was launched directly from the repository.

GitHub Codespaces automatically provisioned a cloud-based Linux development environment and configured the workspace using the repository's devcontainer settings.

After the initialization process completed, the workspace opened successfully without any startup or build errors.

The following checks confirmed that the environment was ready for use:

- Repository files were accessible.
- Terminal access was available.
- Development tools initialized successfully.
- Workspace configuration completed without errors.
- The environment was ready for RISC-V compilation and simulation tasks.

### Screenshot

![Codespace Initialization](sreenshots/codespace_initialization.png)

---

# Step 2: Verify RISC-V Reference Flow

The objective of this step is to verify that the RISC-V toolchain and simulation environment provided in the GitHub Codespace are functioning correctly. This is accomplished by compiling and executing a sample RISC-V program provided in the repository and observing its successful execution.

---

## Step 2.1: Open the Codespace Terminal

After the Codespace environment was initialized successfully, the integrated terminal was opened.

The terminal provides direct access to the pre-installed RISC-V GNU Toolchain, SPIKE ISA Simulator, and other development utilities required for the internship tasks.

### Screenshot

![Codespace Terminal](sreenshots/step2_1_terminal.png)

---

## Step 2.2: Navigate to the Samples Directory

The repository contains a collection of example programs inside the `samples` directory.

Navigate to the samples directory:

```bash
cd samples
```

Display the available files:

```bash
ls -ltr
```

The directory contains example programs and supporting files including:

* `sum1ton.c`
* `1ton_custom.c`
* `load.S`
* `Makefile`

---

## Step 2.3: Compile and Execute the Sample Program

The sample C program `sum1ton.c` calculates the sum of integers from 1 to n.

Compile the program using the RISC-V GNU Compiler:

```bash
riscv64-unknown-elf-gcc -o sum1ton.o sum1ton.c
```

Execute the generated RISC-V binary using the SPIKE ISA Simulator:

```bash
spike pk sum1ton.o
```

### Output

```text
Sum from 1 to 9 is 45
```

The successful execution confirms that:

* The RISC-V GCC toolchain is functioning correctly.
* The executable was generated successfully.
* The SPIKE simulator executed the program correctly.
* The development environment is properly configured.

### Screenshot

![Program Execution](sreenshots/step2_3_program_execution.png)

---

## Step 2.4: Modify and Re-Execute the Program

As recommended in the task, the sample program was modified by changing the value of `n` from `9` to `50`.

### Original Code

```c
int n = 9;
```

### Modified Code

```c
int n = 50;
```

Recompile the modified program:

```bash
riscv64-unknown-elf-gcc -o sum1ton_50.o sum1ton.c
```

Execute the program:

```bash
spike pk sum1ton_50.o
```

### Output

```text
Sum from 1 to 50 is 1275
```

The output matched the expected result, confirming successful compilation and execution of the modified program.

### Screenshot

![Modified Program Output](sreenshots/step2_4_modified_output.png)

---

# Step 3: Clone and Run VSDFPGA Labs

The objective of this step is to verify the VSDFPGA development environment by cloning the FPGA labs repository, compiling a sample firmware application, and executing it using the SPIKE RISC-V simulator.

---

## Step 3.1: Clone the VSDFPGA Labs Repository

Clone the VSDFPGA Labs repository inside the Codespace environment:

```bash
git clone https://github.com/vsdip/vsdfpga_labs.git
```

After cloning, the repository was successfully downloaded and made available for further experimentation.

### Screenshot

![Repository Cloning](sreenshots/step3_1_clone_repo.png)

---

## Step 3.2: Navigate to the Firmware Directory

Move to the firmware directory containing the example RISC-V applications:

```bash
cd vsdfpga_labs/basicRISCV/Firmware
```

### Screenshot

![Firmware Directory](sreenshots/step3_2_firmware_directory.png)

---

## Step 3.3: Examine the Source Program

Open the sample firmware program:

The source code was reviewed to understand the application before compilation.

### Screenshot

![riscv_logo.c](sreenshots/step3_3_source_code.png)

---

## Step 3.4: Compile the Firmware

Compile the firmware using the RISC-V cross compiler:

```bash
riscv64-unknown-elf-gcc -o riscv_logo.o riscv_logo.c
```

The Makefile automatically invokes the RISC-V GCC toolchain and generates the required executable files.

---

## Step 3.5: Execute Using SPIKE Simulator

Run the generated executable using the SPIKE RISC-V simulator:

```bash
spike pk riscv_logo.o
```

The firmware executed successfully and produced the expected output.

---

## Outcome

The VSDFPGA Labs repository was successfully cloned, the sample firmware was compiled using the RISC-V toolchain, and the generated executable was executed successfully using the SPIKE simulator. This verified that the complete software development flow is functioning correctly and that the environment is ready for future FPGA and IP development tasks.

### Screenshot

![SPIKE Execution](sreenshots/step3_5_output.png)

---

# Step 4: Local Machine Preparation and Validation

## Objective

Prepare a local Linux development environment capable of running both the RISC-V reference design and VSDFPGA labs without relying on GitHub Codespaces.

---

## 4.1 Create Local Workspace

A dedicated workspace directory was created and both repositories were cloned.

```bash
mkdir ~/vsd_local_setup
cd ~/vsd_local_setup

git clone https://github.com/vsdip/vsd-riscv2.git
git clone https://github.com/vsdip/vsdfpga_labs.git
```

### Screenshot

![Repository Cloning](sreenshots/repository_clone.png)

---

## 4.2 Install and Configure RISC-V Toolchain

Downloaded and configured the SiFive RISC-V GCC Toolchain (v8.3.0).

Verification:

```bash
which riscv64-unknown-elf-gcc
riscv64-unknown-elf-gcc --version
```

### Screenshot

![Toolchain Verification](sreenshots/gcc_version.png)

---

## 4.3 Build Spike Simulator

Spike ISA Simulator was built from source and installed successfully.

Verification:

```bash
which spike
spike --help
```

### Screenshot

![Spike Installation](sreenshots/spike_install.png)

---

## 4.4 Build Proxy Kernel (PK)

The RISC-V Proxy Kernel (PK) version 1.0.0 was compiled and installed.

Verification:

```bash
git describe --tags --always
```

Output:

```text
v1.0.0
```

### Screenshot

![PK Installation](sreenshots/pk_install.png)

---

## 4.5 Execute Sample Program from vsd-riscv2

Navigate to:

```bash
cd ~/vsd_local_setup/vsd-riscv2/samples
```

Compile:

```bash
riscv64-unknown-elf-gcc -o sum1ton.o sum1ton.c
```

Run:

```bash
spike pk sum1ton.o
```

### Screenshot

![sum1ton Execution](sreenshots/sum1ton_run.png)

---

## 4.6 Execute VSDFPGA Firmware Example

Navigate to:

```bash
cd ~/vsd_local_setup/vsdfpga_labs/basicRISCV/Firmware
```

View source:

```bash
cat riscv_logo.c
```

### Screenshot

![riscv_logo Execution](sreenshots/riscv_logo_program.png)

Compile:

```bash
riscv64-unknown-elf-gcc -o riscv_logo.o riscv_logo.c
```

Run:

```bash
spike pk riscv_logo.o
```

### Screenshot

![riscv_logo Execution](sreenshots/riscv_logo_run.png)

---

## Result

- Successfully prepared a local Linux development environment.
- Installed the SiFive RISC-V GCC Toolchain (v8.3.0).
- Built and installed Spike ISA Simulator.
- Built and installed RISC-V Proxy Kernel (PK v1.0.0).
- Successfully executed the `sum1ton.c` sample program from `vsd-riscv2`.
- Successfully executed the `riscv_logo.c` firmware example from `vsdfpga_labs`.
- Verified readiness for FPGA and RISC-V development workflows.
