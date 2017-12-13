import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * Created on 12.12.2017.
 */
public class Main {
    private final static IntVec2 NEUTRAL_VECTOR = new IntVec2(0, 0);

    public static void main(String[] args) throws Exception {
        String readFile = readFile("input.txt");
        List<IntVec2> vectors = Arrays.asList(readFile.trim().split(",")).stream()
                .map(String::toUpperCase)
                .map(Direction::valueOf)
                .map(Direction::getVec)
                .collect(Collectors.toList());


        IntVec2 tuple = vectors.stream().reduce(NEUTRAL_VECTOR, IntVec2::add);
        int furthest = IntStream.range(0, vectors.size()).mapToObj(l -> vectors.subList(0, l))
                .map(v -> v.stream()
                        .reduce(NEUTRAL_VECTOR, IntVec2::add))
                .mapToInt(IntVec2::length)
                .max()
                .orElse(0);
        System.out.println("[" + tuple.length() + "] " + tuple);
        System.out.println("Max. Dist: " + furthest);
    }


    public static String readFile(String name) throws IOException {
        StringBuilder builder = new StringBuilder();
        try (BufferedReader in = new BufferedReader(new FileReader(new File(name)))) {
            builder.append(in.readLine()).append("\n");
        }

        return builder.toString();
    }

    private static class IntVec2 {
        private final int x, y;

        private IntVec2(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public IntVec2 add(final IntVec2 other) {
            return new IntVec2(x + other.x, y + other.y);
        }

        public int length() {
            return ((Math.abs(x) + Math.abs(y) + Math.abs(x + y)) / 2);
        }

        @Override
        public String toString() {
            return "IntVec2(" + x + ", " + y + ")";
        }
    }

    enum Direction {
        N(0, -1), S(0, 1), NW(-1, 0), NE(1, -1), SW(-1, 1), SE(1, 0);

        public final IntVec2 vec;
        public final int x, y;

        Direction(int x, int y) {
            vec = new IntVec2(x, y);
            this.x = x;
            this.y = y;
        }

        public IntVec2 getVec() {
            return vec;
        }

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }
    }
}
