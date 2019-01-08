#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>


using namespace std;

std::atomic<bool> flagRunning{true};
fstream fnLog;

static void sigCallbackHandler(int signum)
{

  switch(signum) {
    case SIGINT:
      {
        cout << "\n*******************\n* SIGINT received *\n*******************\n";
        cout << "Ctrl+C disabled";
        flagRunning=true;
        break;
      }
    case SIGQUIT:
      {
        cout << "\n*******************\n* SIGQUIT received *\n*******************\n";
        flagRunning=false;
        break;
      }
    case SIGTERM:
      {
        cout << "\n*******************\n* SIGTERM received *\n*******************\n";
        flagRunning=false;
        break;
      }
    case SIGHUP:
      {
        cout << "\n*******************\n* SIGHUP received *\n*******************\n";
        cout << "Ow, warning the terminal died but I'm alive";
        flagRunning=true;
        break;
      }
    case SIGUSR1:
      {
        cout << "\n*******************\n* SIGUSR1 received *\n*******************\n";
        cout << "OK, check update";
        flagRunning=true;
        break;
      }
  }

}


int main(void)
{
  struct sigaction action;

  cout << "PID: " << getpid() << endl;

  // Redirect cout to file /tmp/output.log
  fnLog.open("/tmp/output.log", ios::out); 
  streambuf* stream_buffer_file = fnLog.rdbuf(); 
  cout.rdbuf(stream_buffer_file); 
  
  // Configuring signal Unix
  action.sa_handler = sigCallbackHandler;
  action.sa_flags = 0;
  sigemptyset (&action.sa_mask);
  // SIGINT  - Ctrl+C
  sigaction (SIGINT,  &action, NULL);
  // SIGTERM - Finish Application immediately
  sigaction (SIGTERM, &action, NULL);
  // SIGQUIT - Close Application
  sigaction (SIGQUIT, &action, NULL);
  // SIGHUP  - Terminal disconnect
  sigaction (SIGHUP,  &action, NULL);
  // SIGUSR1 - Custom Signal
  sigaction (SIGUSR1, &action, NULL);

  cout << "Go Loop\n" << flush;
  while(flagRunning) {
   cout << "." << flush;
   this_thread::sleep_for(chrono::milliseconds(500));
  }

  cout << "\nMuhhh, by..." << endl;
  fnLog.close();

  return EXIT_SUCCESS;
}
