import GSLib.Utilities.FileManager;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class day3_2 {
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
    String regex = "(mul\\((\\d{1,3}),(\\d{1,3})\\))|(do\\(\\))|(don't\\(\\))";
    Pattern p = Pattern.compile(regex);
    Matcher m = p.matcher(data);

    // Parse the data
    int sum = 0;
    boolean active = true;
    while (m.find()) {
      if (m.group(0).equals("do()")) active = true;
      else if (m.group(0).equals("don't()")) active = false;
      else {
        int x = Integer.parseInt(m.group(2));
        int y = Integer.parseInt(m.group(3));

        if (active)
          sum += (x * y);
      }
    }

    // Output
    System.out.println("The uncorrupted instructions produce: " + sum);
  }
}
