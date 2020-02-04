using System;
using System.IO;

namespace ConsoleApp1
{
    class Program
    {
        public static void Main(string[] args)
        {
        	checkArguments(args);
        	deleteFilesEndingWith(args[0],args[1]);
        }
        private static void printHelpAndExit()
        {
            Console.WriteLine("Task 1\nUsage : ./task1.exe DIRECTORY FILE_TYPE\nRemoves files of specific FILE_TYPE in subdirectories of DIRECTORY\nExample : ./task1.exe /home .cpp (removes all .cpp files from /home subfolders)\n");
            System.Environment.Exit(0);
        }
        private static void printToFewArgumentsAndExit()
        {
            Console.WriteLine("Too few arguments. Type -h or --help for help");
            System.Environment.Exit(1);
        }
        private static void printToManyArgumentsAndExit()
        {
            Console.WriteLine("Too many arguments. Type -h or --help for help");
            System.Environment.Exit(2);
        }
        private static void checkArguments(String[] args)
        {
            foreach (string arg in args)
            {
                if (arg == "-h" || arg == "--help")
                {
                    printHelpAndExit();
                }
            }
            if (args.Length < 2)
            {
                printToFewArgumentsAndExit();
            }
            else if (args.Length > 2)
            {
                printToManyArgumentsAndExit();
            }
            if (args[1][0] != '.')
            {
                Console.WriteLine("Second argument must start with \".\" (dot)");
                System.Environment.Exit(3);
            }
            FileAttributes attr = File.GetAttributes(args[0]);
            if ((attr & FileAttributes.Directory) != FileAttributes.Directory)
            {
                Console.WriteLine("First argument must be a directory");
                System.Environment.Exit(4);
            }
        }
        private static void deleteFilesEndingWith(string dir, string suffix)
        {
            try
            {
                foreach (string directory in Directory.GetDirectories(dir))
                {
                    foreach (string file in Directory.GetFiles(d))
                    {
                        if (file.EndsWith(suffix))
                        {   
                            File.Delete(file);
                        }
                    }
                    deleteFilesEndingWith(directory,suffix);
                }
            }
            catch (System.Exception excpt)
            {
                Console.WriteLine(excpt.Message);
            }
        }
    }
}
