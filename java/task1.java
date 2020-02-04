import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.lang.*;
import java.util.*;

class Task1{
	public static void main(String[] args) {
		checkArguments(args);
		deleteFilesEndingWith(args[0],args[1]);
	}
	private static void printHelpAndExit(){
		System.out.print("Task 1\nUsage : java Task1 DIRECTORY FILE_TYPE\nRemoves files of specific FILE_TYPE in subdirectories of DIRECTORY\nExample : java Task1 /home .cpp (removes all .cpp files from /home subfolders)\n");
		System.exit(0);
	}
	private static void printToFewArgumentsAndExit(){
		System.out.println("Too few arguments. Type -h or --help for help");
		System.exit(1);
	}
	private static void printToManyArgumentsAndExit(){
		System.out.println("Too many arguments. Type -h or --help for help");
		System.exit(2);
	}
	private static void checkArguments(String[] args){
		for(String arg : args){
			if(arg.equals("-h") || arg.equals("--help")){
				printHelpAndExit();
			}
		}
		if(args.length<2){
			printToFewArgumentsAndExit();
		}
		else if(args.length>2){
			printToManyArgumentsAndExit();
		}
		if(args[1].charAt(0) != '.'){
			System.out.println("Second argument must start with \".\" (dot)");
			System.exit(3);
		}
		if(!(new File(args[0])).isDirectory()){
			System.out.println("First argument must be a directory");
			System.exit(4);
		}
	}
	private static void deleteFilesEndingWith(String dir, String suffix){
		try{
			Files.walk(Paths.get(dir))
    		.filter(file -> Files.isRegularFile(file) && file.toString().endsWith(suffix))
    		.forEach(file -> {
    			try{
    				Files.delete(file);
    			}
    			catch(Exception e){
    				System.out.printf("Cant delete %s\n",file);
    			}
    		});
		}
		catch(IOException e){
			System.out.printf("Cannot open %s\n",dir);
			System.exit(5);
		}
	}
}