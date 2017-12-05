import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;

/**
 * Created on 05.12.2017.
 */
public class JumpVMPart2 extends JumpVM {
    public void run() {
        while (instructionPointer >= 0 && instructionPointer < instructions.size()) {
            int nextInstruction = instructions.get(instructionPointer);
            if (nextInstruction >= 3) {
                instructions.set(instructionPointer, instructions.get(instructionPointer) - 1);
            } else {
                instructions.set(instructionPointer, instructions.get(instructionPointer) + 1);
            }
            instructionPointer += nextInstruction;

            executedInstructions++;
        }
    }

    public String toString() {
        return "JumpVMPart2{" +
                "instructions=" + instructions +
                ", instructionPointer=" + instructionPointer +
                ", executedInstructions=" + executedInstructions +
                '}';
    }

    public static void main(String[] args) throws Exception {
        if (args.length == 0) {
            System.err.println("Require atleast one argument which is the file to read.");
        } else {
            JumpVMPart2 vm = new JumpVMPart2();
            try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(new File(args[0])), "UTF-8"))) {
                String line;
                while ((line = reader.readLine()) != null) {
                    int instruction = Integer.parseInt(line.trim());
                    vm.pushInstruction(instruction);
                }
            }

            System.out.println(vm);
            vm.run();
            System.out.println(vm);
        }
    }
}
