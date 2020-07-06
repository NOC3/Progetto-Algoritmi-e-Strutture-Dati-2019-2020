RunTests:EditDistance.java Tests.java 
	javac EditDistance.java
	javac -cp ./:../Resources/Java/JUnit/hamcrest-core-1.3.jar:../Resources/Java/JUnit/junit-4.12.jar Tests.java
	javac -cp ./:../Resources/Java/JUnit/hamcrest-core-1.3.jar:../Resources/Java/JUnit/junit-4.12.jar TestsMain.java
	java -cp ./:../Resources/Java/JUnit/hamcrest-core-1.3.jar:../Resources/Java/JUnit/junit-4.12.jar TestsMain
	
EditDistanceApp:EditDistance.java EditDistanceApp.java
	javac EditDistance.java EditDistanceApp.java
	java EditDistanceApp ../../dataset/correctme.txt ../../dataset/dictionary.txt 

clean:
	rm *.class