import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;

/**
 * Created on 05.12.2017.
 */
public class JumpVM implements Runnable {
    protected ArrayList<Integer> instructions = new ArrayList<>();
    protected int instructionPointer = 0;
    protected int executedInstructions = 0;

    public void pushInstruction(int instruction) {
        instructions.add(instruction);
    }

    public void run() {
        while (instructionPointer >= 0 && instructionPointer < instructions.size()) {
            int nextInstruction = instructions.get(instructionPointer);
            instructions.set(instructionPointer, instructions.get(instructionPointer) + 1);
            instructionPointer += nextInstruction;

            executedInstructions++;
        }
    }

    public ArrayList<Integer> getInstructions() {
        return instructions;
    }

    public void setInstructions(ArrayList<Integer> instructions) {
        this.instructions = instructions;
    }

    public int getInstructionPointer() {
        return instructionPointer;
    }

    public void setInstructionPointer(int instructionPointer) {
        this.instructionPointer = instructionPointer;
    }

    public int getExecutedInstructions() {
        return executedInstructions;
    }

    public void setExecutedInstructions(int executedInstructions) {
        this.executedInstructions = executedInstructions;
    }

    @Override
    public String toString() {
        return "JumpVM{" +
                "instructions=" + instructions +
                ", instructionPointer=" + instructionPointer +
                ", executedInstructions=" + executedInstructions +
                '}';
    }

    public static void main(String[] args) throws Exception {
        if (args.length == 0) {
            System.err.println("Require atleast one argument which is the file to read.");
        } else {
            JumpVM vm = new JumpVM();
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
