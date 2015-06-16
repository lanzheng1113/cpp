// This example shows if the Base class add new method
// then Derived class may not working as expected

// compile:  javac *.java
// run : java -ea Derived

public class Derived extends Base {
  public boolean foo(long i) {
    System.out.println("Derived::foo called.");
    return true;
  }
  public static void main(String[] args) {
      Derived d = new Derived();
      assert(d.foo(1));
  }
}
