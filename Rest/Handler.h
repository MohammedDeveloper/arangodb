////////////////////////////////////////////////////////////////////////////////
/// @brief abstract class for handlers
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

#ifndef TRIAGENS_FYN_REST_HANDLER_H
#define TRIAGENS_FYN_REST_HANDLER_H 1

#include <Basics/Common.h>
#include <Basics/Exceptions.h>

#include <Rest/Job.h>

namespace triagens {
  namespace rest {

    ////////////////////////////////////////////////////////////////////////////////
    /// @ingroup HttpServer
    /// @brief abstract class for handlers
    ////////////////////////////////////////////////////////////////////////////////

    class  Handler {
      private:
        Handler (Handler const&);
        Handler& operator= (Handler const&);

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief status of execution
        ////////////////////////////////////////////////////////////////////////////////

        enum status_e {
          HANDLER_DONE,
          HANDLER_REQUEUE,
          HANDLER_FAILED
        };

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief constructor
        ////////////////////////////////////////////////////////////////////////////////

        Handler () {
        }

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief destructs a handler
        ////////////////////////////////////////////////////////////////////////////////

        virtual ~Handler () {
        }

      public:


        ////////////////////////////////////////////////////////////////////////////////
        /// @brief returns true if a handler is executed directly
        ////////////////////////////////////////////////////////////////////////////////

        virtual bool isDirect () = 0;

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief returns the job type
        ////////////////////////////////////////////////////////////////////////////////

        virtual Job::JobType type () {
          return Job::READ_JOB;
        }

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief returns the queue name
        ////////////////////////////////////////////////////////////////////////////////

        virtual string const& queue () {
          static string standard = "STANDARD";
          return standard;
        }

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief sets the thread which currently dealing with the job
        ////////////////////////////////////////////////////////////////////////////////

        virtual void setDispatcherThread (DispatcherThread*) {
        }


        ////////////////////////////////////////////////////////////////////////////////
        /// @brief executes a handler
        ////////////////////////////////////////////////////////////////////////////////

        virtual status_e execute () = 0;

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief handle error and delete
        ////////////////////////////////////////////////////////////////////////////////

        virtual void handleError (basics::TriagensError const&) = 0;
    };
  }
}

#endif
