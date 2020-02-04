import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.lang.*;
import java.util.*;

class Task2{
	public static void main(String[] args) {
		checkArguments();
		deleteFilesWithTheSameNameExcept(args[0],args[1]);
	}
	private static void printHelpAndExit(){
		System.out.print("Task 2\nUsage : java Task2 DIRECTORY FILE_TYPE\nRemoves all files with the same name in DIRECTORY except those that have type FILE_TYPE\nExample : java Task2 /home .cpp (removes all files with the same name but .cpp)\n");
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
	private void deleteFilesWithTheSameNameExcept(String dir, String suffix){
		List<Path> filesToDelete = new ArrayList<>();
		try{
			Files.walk(Paths.get(dir))
    		.filter(file -> Files.isRegularFile(file))
    		.forEach(file -> {
				Files.walk(Paths.get(dir))
        		.filter(file2 -> Files.isRegularFile(file2))
        		.forEach(file2 -> {
        			if(!file.equals(file2)){
        				String file2Name = file2.getFileName().toString().substring(0,file2.getFileName().toString().lastIndexOf("."));
        				if(file.getFileName().toString().startsWith(file2Name)){
        					if(!file2.toString().endsWith(suffix)){
        						if(!filesToDelete.contains(file2)){
        							filesToDelete.add(file2);
        						}
        					}
        				}
        			}
        		});
			});
    		filesToDelete.forEach(file -> {
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