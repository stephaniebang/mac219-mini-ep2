library(ggplot2)

# turn off scientific notation
options(scipen = 999)

# path to results folder
path <- './results/'

# get file list in paths
files <- dir(path)

# function to print results statistics
printStatistics <- function(table) {
  times <- table$time
  m <- mean(times)
  s <- sd(times)
  
  cat(
    "Mean: ", m, "s\n",
    "Min: ", min(times), "s\n",
    "Max: ", max(times), "s\n",
    "SD: ", s, "s\n",
    sep=""
  )
}


## TESTS WITH matrix_dgemn_0 ------------------------------------------------

cat("*** matrix_dgemn_0 results\n")

t <- read.table(paste0(path, files[1]), header=T, sep=';')

# view table and plot
View(t)

ggplot(t, aes(round(t$time))) +
  geom_histogram(binwidth=1) +
  labs(
    title="matrix_dgemn_0 runtime",
    subtitle="Ran 40 times",
    y="Number of occurrences",
    x="Time (s)"
  )

# save plot
suppressMessages(ggsave("results/matrix_dgemn_0.png"))

# get statistics
printStatistics(t)


## TESTS WITH matrix_dgemn_1 ------------------------------------------------

cat("\n*** matrix_dgemn_1 results\n")

t <- read.table(paste0(path, files[2]), header=T, sep=';')

# view table and plot
View(t)

ggplot(t, aes(round(t$time))) +
  geom_histogram(binwidth=1) +
  labs(
    title="matrix_dgemn_1 runtime",
    subtitle="Ran 40 times",
    y="Number of occurrences",
    x="Time (s)"
  )

# save plot
suppressMessages(ggsave("results/matrix_dgemn_1.png"))

# get statistics
printStatistics(t)



## TESTS WITH IF CHAIN SIZE -----------------------------------------------

cat("\n*** matrix_dgemn_1 results\n")

t <- read.table(paste0(path, files[3]), header=T, sep=';')

# view table and plot
View(t)

ggplot(t, aes(round(t$time))) +
  geom_histogram(binwidth=1) +
  labs(
    title="matrix_dgemn_2 runtime",
    subtitle="Ran 40 times",
    y="Number of occurrences",
    x="Time (s)"
  )

# save plot
suppressMessages(ggsave("results/matrix_dgemn_2.png"))

# get statistics
printStatistics(t)
