import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.file.*;
import java.lang.*;
import java.util.*;
import java.time.Instant;

class Task3{
    public static long size = 0;
    public static long part1Returns = 0;
    public static long part2Returns = 0;
    public static void main(String[] args) {
        try {
            checkArguments(args);
        }
        catch (Exception e){
            System.out.println("Error in checking arguments");
            System.exit(1);
        }
        doAllTasks(args[0]);
    }
    private static void printHelpAndExit(){
        System.out.print("Task 3\nUsage : java Task3 DIRECTORY\n1) Prints files were changed last hour\n2) Prints 10 the oldest files\n3) Copies 10 the freshest into directory \"backup\"\n");
        System.exit(0);
    }
    private static void printToFewArgumentsAndExit(){
        System.out.println("Too few arguments. Type -h or --help for help");
        throw new ArrayIndexOutOfBoundsException();
    }
    private static void printToManyArgumentsAndExit(){
        System.out.println("Too many arguments. Type -h or --help for help");
        throw new ArrayIndexOutOfBoundsException();
    }
    public static void checkArguments(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
        for(String arg : args){
            if(arg.equals("-h") || arg.equals("--help")){
                printHelpAndExit();
            }
        }
        if(args.length<1){
            printToFewArgumentsAndExit();
        }
        else if(args.length>1){
            printToManyArgumentsAndExit();
        }
        if(!(new File(args[0])).isDirectory()){
            System.out.println("First argument must be a directory");
            throw new FileNotFoundException();
        }
    }
    public static void doAllTasks(String dir){
        printFilesWereChangedLast(dir,60);
        printOldestFilesAndSumSize(dir,10);
        copyFreshestFilesInto(dir,"backup",10);
    }
    public static void printFilesWereChangedLast(String dir, int minutes){
        try{
            System.out.println("Files were changed last hour : ");
            Files.walk(Paths.get(dir))
                    .filter(file -> Files.isRegularFile(file))
                    .forEach(file -> {
                        if(Instant.now().toEpochMilli() - file.toFile().lastModified() < minutes*60*1000){
                            System.out.println(file);
                            part1Returns++;
                        }
                    });
        }
        catch(IOException e){
            System.out.printf("Cannot open %s\n",dir);
            System.exit(5);
        }
    }
    public static void printOldestFilesAndSumSize(String dir,int limit){
        try{
            System.out.println("Ten oldest files : ");
            Files.walk(Paths.get(dir))
                    .filter(file -> Files.isRegularFile(file)).sorted(Comparator.comparing(x -> x.toFile().lastModified(),Comparator.reverseOrder())).limit(limit)
                    .forEach(file -> {
                        System.out.println(file);
                        part2Returns++;
                        size += file.toFile().length();
                    });
            System.out.printf("Their size : %d bytes\n",size);
        }
        catch(IOException e){
            System.out.printf("Cannot open %s\n",dir);
            System.exit(5);
        }
    }
    public static void copyFreshestFilesInto(String dir,String nameDirForBackup,int limit){
        try{
            File backupDir = new File(new File(dir), nameDirForBackup);
            if(!Files.exists(backupDir.toPath()))
                Files.createDirectory(backupDir.toPath());
            Files.walk(Paths.get(dir))
                    .filter(file -> Files.isRegularFile(file)).sorted(Comparator.comparing(x -> x.toFile().lastModified())).limit(limit)
                    .forEach(file -> {
                        try{
                            File fileToCopy = new File(backupDir,file.getFileName().toString());
                            if(!Files.exists(fileToCopy.toPath()))
                                Files.copy(file,fileToCopy.toPath());
                        }
                        catch(IOException e){
                            System.out.printf("Error in copy %s\n",file.toString());
                        }
                    });
        }
        catch(IOException e){
            System.out.printf("Cannot open %s\n",dir);
            System.exit(5);
        }
    }
}