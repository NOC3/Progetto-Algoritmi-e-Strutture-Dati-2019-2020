import java.io.*;
import java.util.*;
import java.nio.file.*;

public class EditDistanceApp {
  private static String dictionary;

  /*output file path*/
  private static final String output_file="../../dataset/corrected.txt"; 

  public static void main(String[] args){
    if(args.length<2){
      print_err("Syntax error, two parameters needed!");            
    }else{
      long startTime=java.lang.System.currentTimeMillis(), stopTime;
      double time;
      EditDistanceApp.dictionary = args[1];
      File textFile = new File(args[0]);
      try{
        eval_file_distances(textFile);
      }catch(Exception e){
        print_err(e.getMessage());
        System.exit(0);
      }
      stopTime = java.lang.System.currentTimeMillis();
      time = (double)(stopTime-startTime)/1000;
      System.out.println("File created: " + output_file);
      System.out.println("Total execution time: " + time+ " sec");      
    }
  }

  private static void print_err(String err){
    System.out.println("Error: "+err);
    System.out.println("Parameters in Makefile must have the following form:\n\targs[0]='filetocorrect'\n\targs[1]='dictionary'\n");
  }

  /*parse file word by word*/
  private static void eval_file_distances(File correctme) throws IOException{
    File corrected= new File(EditDistanceApp.output_file); /*output file with edit distances for each word*/
    Scanner cm = null; /*Scanner of file to correct*/
    
    if(corrected.exists()) /*check output file*/
      corrected.delete(); /*delete if exists*/
    corrected.createNewFile();

    cm = new Scanner (correctme);
    
    while (cm.hasNextLine()) {
      Scanner line = new Scanner(cm.nextLine());
      while (line.hasNext()) {
        String s = line.next();
        /*delete punctuation and converting to lower case*/
        find_best_distances(s.replaceAll("\\p{Punct}", "").toLowerCase()); 
      }
    }
    cm.close();
  }

  /*find and print lowest edit distances words*/
  private static void find_best_distances(String word)throws IOException{
    File dictionary = new File(EditDistanceApp.dictionary); 
    List<String> l= new LinkedList<String>(); /*contains words that have teh lowest edit distances*/
    int best=Integer.MAX_VALUE; /*fictitious value for the first loop*/
    Scanner dict = null;
    long startTime=0, stopTime;
    double time;
    dict = new Scanner(dictionary);
    startTime = java.lang.System.currentTimeMillis(); 

    while(dict.hasNextLine()){
      String s=dict.next();
      if(!((Math.abs(s.length()-word.length())>best))){
        int tmp=EditDistance.edit_distance_dyn(word, s);
        if(best>tmp){
          best=tmp;
          l.clear();
          l.add(s);
        } else if(best==tmp){
          l.add(s);
        }
        if(tmp==0) /*if target word is correct break*/
          break;
      }
      dict.nextLine();
    }
    stopTime = java.lang.System.currentTimeMillis();
    time = (double)(stopTime-startTime)/1000; /*time passed to find best distances*/

    String textToAppend = "Target word: "+ word + ", lowest edit distance found: "+ best + ", words found: ";

    for(int i=0; i<l.size(); i++)
      textToAppend=textToAppend+l.get(i) + " "; /*appends found words to the current string*/
        
    textToAppend+= "\nexecution time:" + Double.toString(time)+" sec.\n\n"; /*appends passed time*/
    Files.write(Paths.get(EditDistanceApp.output_file), textToAppend.getBytes(), StandardOpenOption.APPEND); /*append result to output file*/
    dict.close();
  }
}