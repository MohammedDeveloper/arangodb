////////////////////////////////////////////////////////////////////////////////
/// @brief application server scheduler implementation
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2011 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
/// @author Copyright 2009-2011, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_FYN_APPLICATION_SERVER_APPLICATION_SERVER_SCHEDULER_IMPL_H
#define TRIAGENS_FYN_APPLICATION_SERVER_APPLICATION_SERVER_SCHEDULER_IMPL_H 1

#include "ApplicationServer/ApplicationServerImpl.h"

#include <Basics/ConditionVariable.h>

////////////////////////////////////////////////////////////////////////////////
/// @page CommandLineSchedulerTOC
///
/// <ol>
///  <li>scheduler.backend</li>
///  <li>scheduler.threads</li>
/// </ol>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @page CommandLineScheduler Command-Line Options for Communication
///
/// @copydoc CommandLineSchedulerTOC
/// <hr>
///
/// @copydetails triagens::rest::ApplicationServerSchedulerImpl::_backend
///
/// @copydetails triagens::rest::ApplicationServerSchedulerImpl::_nrSchedulerThreads
////////////////////////////////////////////////////////////////////////////////

namespace triagens {
  namespace rest {
    class Task;

    ////////////////////////////////////////////////////////////////////////////////
    /// @brief application server scheduler implementation
    ////////////////////////////////////////////////////////////////////////////////

    class ApplicationServerSchedulerImpl : public ApplicationServerImpl {
      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief constructor
        ////////////////////////////////////////////////////////////////////////////////

        ApplicationServerSchedulerImpl (string const& description, string const& version);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief destructor
        ////////////////////////////////////////////////////////////////////////////////

        ~ApplicationServerSchedulerImpl ();

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void allowMultiScheduler (bool value = true) {
          _multiSchedulerAllowed = value;
        }

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        Scheduler* scheduler () const {
          return _scheduler;
        }

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void buildScheduler ();

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void buildSchedulerReporter ();

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void buildControlCHandler ();

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief installs a signal handler
        ////////////////////////////////////////////////////////////////////////////////

        void installSignalHandler (SignalTask*);

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        bool addressReuseAllowed () {
          return reuseAddress;
        }

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void start ();

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void wait ();

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void beginShutdown ();

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void shutdown ();

      protected:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief register a new task
        ////////////////////////////////////////////////////////////////////////////////

        void registerTask (Task*);

      protected:

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        void setupOptions (map<string, basics::ProgramOptionsDescription>&);

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        bool parsePhase1 ();

        ////////////////////////////////////////////////////////////////////////////////
        /// {@inheritDoc}
        ////////////////////////////////////////////////////////////////////////////////

        bool parsePhase2 ();

      protected:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief intervall for reports
        ////////////////////////////////////////////////////////////////////////////////

        double _reportIntervall;

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief is a multi-threaded scheduler allowed
        ////////////////////////////////////////////////////////////////////////////////

        bool _multiSchedulerAllowed;

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief number of scheduler threads
        ///
        /// @CMDOPT{--scheduler.threads @CA{arg}}
        ///
        /// An integer argument which sets the number of threads to use in the IO
        /// scheduler. The default is 1.
        ////////////////////////////////////////////////////////////////////////////////

        uint32_t _nrSchedulerThreads;

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief scheduler backend
        ///
        /// @CMDOPT{--scheduler.backend @CA{arg}}
        ///
        /// The I/O method used by the event handler. The default (if this option is
        /// not specified) is to try all recommended backends. This is platform
        /// specific. See libev for further details and the meaning of select, poll
        /// and epoll.
        ////////////////////////////////////////////////////////////////////////////////

        uint32_t _backend;

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief allow port to be reused
        ////////////////////////////////////////////////////////////////////////////////

        bool reuseAddress;

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief minimum number of file descriptors
        ////////////////////////////////////////////////////////////////////////////////

        uint32_t descriptorMinimum;


      private:
        void adjustFileDescriptors ();

      private:
        Scheduler* _scheduler;
        basics::ConditionVariable _schedulerCond;
        bool _shutdownInProgress;

        vector<Task*> _tasks;
    };
  }
}

#endif

