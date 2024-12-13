import GSLib.Utilities.FileManager;
import java.util.regex.*;

public class day3_1 {
  public static void main(String[] args) {
    // Make sure the input file name is passed in as an argument
    if (args.length < 1) {
      System.err.println("Error: include the name of the input");
      throw new RuntimeException();
    }

    // Create filepath
    String path = "../resources/";
    String filepath = path + args[0];

    // Read file
    String data = FileManager.readFile(filepath);

    // Regex
    String regex = "mul\\((\\d{1,3}),(\\d{1,3})\\)";
    Pattern p = Pattern.compile(regex);
    Matcher m = p.matcher(data);

    // Parse file
    int sum = 0;
    while (m.find()) {
      int x = Integer.parseInt(m.group(1));
      int y = Integer.parseInt(m.group(2));
      sum += (x * y);
    }

    // Total Output
    System.out.println("The uncorrupted instructions produce: " + sum);
  }
}
