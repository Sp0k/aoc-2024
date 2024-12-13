import GSLib.Utilities.FileManager;

public class day4_2 {
  public static void main(String[] args) {
    if (args.length != 1) {
      throw new RuntimeException("Please add the input file");
    }

    // Read file's data
    String filename = "../resources/" + args[0];
    String data = FileManager.readFile(filename);
    System.out.println("WORD SEARCH:\n\n" + data);
    String[] wordSearch = data.split("\n");

    // Parse input
    int sum = 0;
    for (int i = 1; i < wordSearch.length - 1; i++) {
      for (int j = 1; j < wordSearch[i].length() - 1; j++) {
        // Find an 'A'
        if (wordSearch[i].charAt(j) == 'A') {
          boolean branch1 = false;
          boolean branch2 = false;

          // Get the tips of the X's branches
          char tl = wordSearch[i - 1].charAt(j - 1);
          char tr = wordSearch[i - 1].charAt(j + 1);
          char bl = wordSearch[i + 1].charAt(j - 1);
          char br = wordSearch[i + 1].charAt(j + 1);

          // Check the branches
          if ((tl == 'M' && br == 'S') || (tl == 'S' && br == 'M'))
            branch1 = true;

          if ((tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M'))
            branch2 = true;

          // Update count
          if (branch1 && branch2)
            sum++;
        }
      }
    }

    // Output
    System.out.println("Total 'XMAS' apperances: " + sum);
  }
}
