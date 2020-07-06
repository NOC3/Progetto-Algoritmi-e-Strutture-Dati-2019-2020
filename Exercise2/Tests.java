import static org.junit.Assert.*;
import org.junit.*;


public class Tests{
  @Test
  public void testVoidStr() {
    Integer aNumber = Integer.valueOf(EditDistance.edit_distance("", ""));
    assertSame("should be same", aNumber, 0);
    aNumber = Integer.valueOf(EditDistance.edit_distance_dyn("", ""));
    assertSame("should be same", aNumber, 0);
  }
  
  @Test
  public void testEdit0() {
    Integer aNumber = Integer.valueOf(EditDistance.edit_distance("pioppo", "pioppo"));
    assertSame("should be same", aNumber, 0);
    aNumber = Integer.valueOf(EditDistance.edit_distance_dyn("pioppo", "pioppo"));
    assertSame("should be same", aNumber, 0);
  }

  @Test
  public void testEdit1() {
    Integer aNumber = Integer.valueOf(EditDistance.edit_distance("casa", "cassa"));
    assertSame("should be same", aNumber, 1);
    aNumber = Integer.valueOf(EditDistance.edit_distance_dyn("casa", "cassa"));
    assertSame("should be same", aNumber, 1);
  }
  
  @Test
  public void testEdit2() {
    Integer aNumber = Integer.valueOf(EditDistance.edit_distance("casa", "cara"));
    assertSame("should be same", aNumber, 2);
    aNumber = Integer.valueOf(EditDistance.edit_distance_dyn("casa", "cara"));
    assertSame("should be same", aNumber, 2);
  }

  @Test
  public void testEdit3() {
    Integer aNumber = Integer.valueOf(EditDistance.edit_distance("vinaio", "vino"));
    assertSame("should be same", aNumber, 2);
    aNumber = Integer.valueOf(EditDistance.edit_distance_dyn("vinaio", "vino"));
    assertSame("should be same", aNumber, 2);
  }
  
  @Test
  public void testEdit4() {
    Integer aNumber = Integer.valueOf(EditDistance.edit_distance("tassa", "passato"));
    assertSame("should be same", aNumber, 4);
    aNumber = Integer.valueOf(EditDistance.edit_distance_dyn("tassa", "passato"));
    assertSame("should be same", aNumber, 4);
  }

  public void testEdit5() {
    Integer aNumber = Integer.valueOf(EditDistance.edit_distance("Lavieestbelle", "La vie est belle"));
    assertSame("should be same", aNumber, 3);
    aNumber = Integer.valueOf(EditDistance.edit_distance_dyn("Lavieestbelle", "La vie est belle"));
    assertSame("should be same", aNumber, 3);
  }
}