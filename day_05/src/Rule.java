import java.util.ArrayList;

public class Rule {
  private int ruleInt;
  private ArrayList<Integer> numbers;

  public Rule(int rn, int n) {
    this.ruleInt = rn;

    this.numbers = new ArrayList<Integer>();
    numbers.add(n);
  }

  public int getRuleInt() {
    return this.ruleInt;
  }

  public int[] getRuleNumbers() {
    return this.numbers.stream().mapToInt(Integer::intValue).toArray();
  }

  public void addRuleNumber(int n) {
    if (!numbers.contains(n))
      this.numbers.add(n);
  }

  public boolean doesContain(int n) {
    return numbers.contains(n);
  }
}
