/*
 cd /scratch/summit/rata8212/PRJ007_Histogram
 make

 or

 g++ -std=c++11 histogram.cpp CommFunc.cpp -o histogram
 cp histogram /work/KellerLab/opt/bin
*/

#include <iostream>
//#include <sstream> // istringstream
#include <string>
#include <vector>
#include <cstdio> //for printf
#include <cmath> // for log2
#include <cctype> // for isdigit
#include "CommFunc.h"


//defalut values
#define VER 1.1
#define BINFORMAT "[%12.6f, %12.6f) |%9u| "
#define MAXDOTS 40




void ras_help(void);


int main(int argc, char *argv[])
{
    //proc params
    int nbin=0;
    std::string binformat=BINFORMAT;
    int maxdots=MAXDOTS; // len=2*maxdots
    std::string dot_symbol="∎";
    std::string sep=" ";
    std::string in_file_name="";
    bool has_file=false;
    bool has_header=false;
    bool has_sammary=false;
    std::string summary_type="";
    unsigned col_num=1; // 1-based col number

    for (int i=1; i<argc; i++)
    {
        std::string s(argv[i]);
        if (s=="--help" || s=="-h")
        {
            ras_help();
            return 0;
        }
        else if (s=="--sep")
        {
            sep = std::string(argv[++i]);
            if (sep=="tab")
                sep='\t';
        }
        else if (s=="--nbin")
        {
            nbin = std::stod(std::string(argv[++i]));
        }
        else if (s=="--header")
        {
            has_header = true;
        }
        else if (s=="--summary")
        {
            has_sammary = true;
            summary_type = std::string(argv[++i]);
        }
        else if (s=="--file" || s=="-f")
        {
            has_file = true;
            in_file_name = std::string(argv[++i]);
        }
        else if (s=="--column" || s=="-c")
        {
            col_num = std::stod(argv[++i]);
        }
        else if (s=="--binformat")
        {
            binformat = std::string(argv[++i]);
        }
        else if (s=="--maxdots")
        {
            maxdots = std::stod(std::string(argv[++i]));
        }
        else if (s=="--dotsymbol")
        {
            dot_symbol = std::string(argv[++i]);
        }
        else
        {
            std::cout << "# Error: unknown parameter [" << s << "]" << std::endl;
            return -1;
        }
    }

    
    /////////////////////////////////////////////////////////
    // reading data from std::in or a file
    std::vector<double> data;
    int num_na = 0;

    if(has_file)
    {
        std::ifstream ifile(in_file_name.c_str());
        if (!ifile.is_open())
        {
            std::cout << "# Error: Unable to open file [" << in_file_name << "]" << std::endl;
            return -1;
        }

        int col_idx=col_num-1;
        if (col_num<=0)
        {
            std::cout << "# Error: column number should be > 1." << std::endl;
            return -1;
        }
        if(col_num>CommFunc::ras_FileColNumber(in_file_name, sep))
        {
            std::cout << "# Error: Column number is incorrect." << std::endl;
            return -1;
        }
        
        
        std::string line;
        if(has_header) // discard the first line
        {
            std::getline(ifile, line);
        }
        while (std::getline(ifile,line) )
        {
            std::vector<std::string> arr = CommFunc::split(line,sep);
            std::string s = arr[col_idx];
            if (isdigit(s[0]))
                data.push_back(std::stod(s));
            else num_na++;
        }
        ifile.close();
    }
    else{ // read data from stdin
        int col_idx = col_num - 1;
        if (col_num<=0)
        {
            std::cout << "# Error: column number should be > 1." << std::endl;
            return -1;
        }
        if(has_header) // discard the first line
        {
            std::string line;
            std::getline(std::cin, line);
        }
        
        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> arr = CommFunc::split(line,sep);
            std::string s = arr[col_idx];
            if (isdigit(s[0]))
                data.push_back(std::stod(s));
            else num_na++;
        }
    }
    
    // statistics
    if (data.size()==0)
    {
        std::cout << "# Error: No data!" << std::endl;
        return -1;
    }
    
    /////////////////////////////////////////////////////////
    // compute stats
    double data_size = data.size();
    double data_min  = *std::min_element(std::begin(data), std::end(data));
    double data_max  = *std::max_element(std::begin(data), std::end(data));
    double data_mean = CommFunc::mean(data);
    double data_sum  = CommFunc::sum(data);
    double data_var  = CommFunc::var(data);
    double data_sd   = CommFunc::sd(data);
    double data_med  = CommFunc::median(data);
    
    if(has_sammary)
    {
        if (summary_type=="NumSamples")
        {
            std::cout << data.size() << std::endl;
            return 0;
        }
        else if (summary_type=="sum")
        {
            std::cout << data_sum << std::endl;
            return 0;
        }
        else if (summary_type=="mean")
        {
            std::cout << data_mean << std::endl;
            return 0;
        }
        else if (summary_type=="min")
        {
            std::cout << data_min << std::endl;
            return 0;
        }
        else if (summary_type=="max")
        {
            std::cout << data_max << std::endl;
            return 0;
        }
        else if (summary_type=="var")
        {
            std::cout << data_var << std::endl;
            return 0;
        }
        else if (summary_type=="sd")
        {
            std::cout << data_sd << std::endl;
            return 0;
        }
        else if (summary_type=="med")
        {
            std::cout << data_med << std::endl;
            return 0;
        }
    }
    
    std::cout << "# NumSamples = " << data_size << std::endl;
    std::cout << "# Num NAs    = " << num_na << std::endl;
    std::cout << "# Min        = " << data_min << std::endl;
    std::cout << "# Max        = " << data_max << std::endl;
    std::cout << "# Mean       = " << data_mean << std::endl;
    std::cout << "# Sum        = " << data_sum << std::endl;
    std::cout << "# Variance   = " << data_var << std::endl;
    std::cout << "# SD         = " << data_sd << std::endl;
    std::cout << "# Median     = " << data_med << std::endl;
    
    

    // default values
    if (nbin==0)
    {
        //nbin=std::sqrt(data_size);
        nbin=log2(data_size)+1;
    }
    
    std::vector<long int> hist(nbin,0);
    double bin_width = (data_max-data_min)/nbin;
    for (unsigned int idata=0; idata<data_size; idata++)
    {
        int ibin = (data[idata]-data_min)*nbin/(data_max-data_min);
        if (ibin<nbin)
            hist[ibin]++;
        else
            hist[nbin-1]++; // for data_max
    }
    
    unsigned bin_max = *std::max_element(std::begin(hist), std::end(hist));
    unsigned dot_count = 1;
    if (bin_max > maxdots)
    {
        dot_count = bin_max/maxdots;
    }
    
    std::cout << "# each " << dot_symbol << " represents a count of " << dot_count << std::endl;
    std::cout << "# --------------------------------------" << std::endl;
    for (int ibin=0; ibin<nbin; ibin++)
    {
        //std::cout << data_min+ << hist[ibin] << std::endl;
        printf(binformat.c_str(), data_min+ibin*bin_width, data_min+(ibin+1)*bin_width, hist[ibin]);
        for (int idots=0; idots<hist[ibin]/dot_count; idots++) printf("%s",dot_symbol.c_str());
        
        printf("\n");
    }
    std::cout << "# --------------------------------------" << std::endl;
    
    
    return 0;
}




void ras_help(void)
{
    std::cout << " histogram C 2016; By: Rasool Tahmasbi" << std::endl;
    std::cout << " Ver: " << VER << std::endl;
    std::cout << std::endl;

    std::cout << " Usage:" << std::endl;
    std::cout << "      cat data.txt | histogram" << std::endl;
    std::cout << "      histogram -f [data.txt] -c [N]" << std::endl;
    std::cout << "         default: -c [1]" << std::endl;
    std::cout << "         where [data.txt] is data file and can have multiple columns." << std::endl;
    std::cout << std::endl;
    
    
    std::cout << " Parameters:" << std::endl;
    std::cout << "      --file | -f [file]" << std::endl;
    std::cout << "      --sep [space]; for TAB seperated data use [--sep $'\\t'], or [--sep tab]." << std::endl;
    std::cout << "      --nbin [N]" << std::endl;
    std::cout << "      --column | -c [col_number]; default 1" << std::endl;
    std::cout << "      --header" << std::endl;
    std::cout << "      --summary [NumSamples | sum | mean | min | max | var | sd | med]" << std::endl;
    std::cout << "      --binformat [\"" << BINFORMAT << "\"]" << std::endl;
    std::cout << "      --help | -h" << std::endl;
    std::cout << "      --maxdots [" << MAXDOTS << "]" << std::endl;
    std::cout << "      --dotsymbol [∎]" << std::endl;
    std::cout << "        Note: for * you should type \"*\". You can also use Emoji & Symbols." << std::endl;
    std::cout << std::endl;

}






