import GSLib.Utilities.FileManager;
import java.util.ArrayList;

public class day5_1 {
  private static ArrayList<Rule> rules;

  public static boolean rulesContain(int n) {
    for (Rule r : rules) {
      if (r.getRuleInt() == n)
        return true;
    }

    return false;
  }

  public static Rule getRule(int n) {
    for (Rule r : rules) {
      if (r.getRuleInt() == n)
        return r;
    }

    return null;
  }

  public static void main(String[] args) {
    if (args.length != 1)
      throw new RuntimeException("Please add the input file");

    // Read file's data
    String filepath = "../resources/" + args[0];
    String data = FileManager.readFile(filepath);
    String[] splitData = data.split("\n\n");
    String[] ruleData = splitData[0].split("\n");
    String[] updateData = splitData[1].split("\n");

    // Create the rules
    rules = new ArrayList<Rule>();
    for (int i = 0; i < ruleData.length; i++) {
      int ruleNum = Integer.parseInt(ruleData[i].substring(0, 2));
      int ruleAdd = Integer.parseInt(ruleData[i].substring(3));

      if (rules.isEmpty() || !rulesContain(ruleNum))
        rules.add(new Rule(ruleNum, ruleAdd));
      else {
        Rule r = getRule(ruleNum);
        r.addRuleNumber(ruleAdd);
      }
    }

    // Parse data
    int sum = 0;
    for (String s : updateData) {
      // Turn the string into an integer array
      String[] updateString = s.split(",");
      int[] update = new int[updateString.length];
      for (int i = 0; i < updateString.length; i++)
        update[i] = Integer.parseInt(updateString[i]);

      // Check update validity
      boolean isValid = true;
      for (int i = 1; i < update.length; i++) {
        if (rulesContain(update[i])) {
          Rule r = getRule(update[i]);

          for (int j = i - 1; j >= 0; j--) {
            if (r.doesContain(update[j])) {
              isValid = false;
              break;
            }
          }

          if (!isValid)
            break;
        }
      }

      if (isValid) {
        int midpoint = update.length / 2;
        sum += update[midpoint];
      }
    }

    System.out.println("The total is: " + sum);
  }
}
