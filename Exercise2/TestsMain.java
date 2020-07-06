import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;

public class TestsMain {
    public static void main(String[] args) {
        Result result = JUnitCore.runClasses(Tests.class);
    
        for (Failure failure : result.getFailures()) {
          System.out.println(failure.toString());
        }
    
        System.out.println("Final result of tests: " + ((result.wasSuccessful()) ? "PASSED!" : "ERROR!"));
      } 
}