import (
    "os"
    "fmt"
    "strings"
    "strconv"
    "io/ioutil"
    "time"
    "runtime"
    "wordsort"
)

func main() {
    runtime.GOMAXPROCS(runtime.NumCPU()) //Use all available CPUs

    if len(os.Args) < 4 {
        fmt.Println("Too few arguments. You must supply thread-count, input and output files")
        return
    }

    threadCount, err := strconv.Atoi(os.Args[1])
    inputfile := os.Args[2]
    outputfile := os.Args[3]

    if err != nil {
        fmt.Println("Thread-count must be a number")
        return
    }

    timeFunc("WordSort", func() {
        if bytes, err := ioutil.ReadFile(inputfile); err == nil {
            filelines := strings.Split(string(bytes), "\n")
            words := filelines[1:]
            sortedWords := sortWords(words, threadCount)
            stringToWrite := strconv.Itoa(len(sortedWords)) + "\n" + strings.Join(sortedWords, "\n")

            ioutil.WriteFile(outputfile, []byte(stringToWrite), 0777)
        } else {
            fmt.Println(err)
        }
    })
}

func timeFunc(event string, action func()) {
    start := time.Now()
    action()
    duration := time.Since(start)

    fmt.Printf("%s finished in %d ms\n", event, duration / time.Millisecond) 
}

func sortWords(words []string, threadCount int) []string {
    wordCount := len(words)
    wordsPerThread := wordCount / threadCount
    wordsRemainingPerThread := wordCount % threadCount
    
    sortedWordSlices := make(chan []string)
    sortIndex := 0

    for i:= 0; i < threadCount; i++ {
        wordsForThread := wordsPerThread

        if wordsRemainingPerThread > 0 {
            wordsForThread++
            wordsRemainingPerThread--
        }

        go wordsort.SortSlice(words[sortIndex:sortIndex + wordsForThread], sortedWordSlices)
        sortIndex += wordsForThread
    }

    var cachedResult *[]string
    for remainingThreads := threadCount; remainingThreads > 0; {
        newResult := <- sortedWordSlices

        if cachedResult == nil {
            cachedResult = &newResult
            remainingThreads--
        } else {
            go wordsort.JoinSortedSlices(*cachedResult, newResult, sortedWordSlices)
            cachedResult = nil
        }
    }

    return *cachedResult
}
