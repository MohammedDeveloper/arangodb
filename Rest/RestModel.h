////////////////////////////////////////////////////////////////////////////////
/// @brief abstract rest model
///
/// @file
/// This file contains the description of the rest model used.
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
/// @author Copyright 2010-2011, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_FYN_REST_REST_MODEL_H
#define TRIAGENS_FYN_REST_REST_MODEL_H 1

#include <Basics/Common.h>

#include <Basics/ProgramOptionsDescription.h>
#include <Rest/ApplicationServer.h>

namespace triagens {
  namespace rest {
    class ApplicationHttpServer;
    class HttpHandler;
    class HttpHandlerFactory;
    class HttpRequest;
    class HttpServer;
    class HttpsServer;
    class RestServer;

    class ApplicationHttpsServer;

    class ApplicationServerDispatcher;

    ////////////////////////////////////////////////////////////////////////////////
    /// @ingroup RestServer
    /// @brief abstract rest model
    ////////////////////////////////////////////////////////////////////////////////

    class RestModel : noncopyable {
      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief description for extensions via handlers
        ////////////////////////////////////////////////////////////////////////////////

        struct HandlerDescription {
          bool isPrefix;
          string path;
          HttpHandler* (*method) (HttpRequest*, void*);
          void* data;
        };

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief rest extensions
        ////////////////////////////////////////////////////////////////////////////////

        class Extensions : noncopyable {
          public:

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief virtual destructor
            ////////////////////////////////////////////////////////////////////////////////

            virtual ~Extensions () {
            }

          public:

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief allows a multi scheduler
            ////////////////////////////////////////////////////////////////////////////////

            virtual bool allowMultiScheduler () {
              return true;
            }

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief returns the version
            ////////////////////////////////////////////////////////////////////////////////

            virtual string serverVersion () {
              return "unknown (not set in RestModel)";
            }

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief shows the port options
            ////////////////////////////////////////////////////////////////////////////////

            virtual bool showPortOptions () {
              return true;
            }

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief returns model specific options
            ////////////////////////////////////////////////////////////////////////////////

            virtual map<string, basics::ProgramOptionsDescription> options ();

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief returns list of extensions
            ////////////////////////////////////////////////////////////////////////////////

            virtual vector<HandlerDescription> handlers ();

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief returns header and body size restrictions
            ////////////////////////////////////////////////////////////////////////////////

            virtual pair<size_t, size_t> sizeRestrictions ();

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief called to build a handler factory
            ////////////////////////////////////////////////////////////////////////////////

            virtual HttpHandlerFactory* buildHandlerFactory (RestModel*);

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief called after arguments are parsed
            ////////////////////////////////////////////////////////////////////////////////

            virtual void checkArguments (ApplicationServer*);

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief called after arguments are checked
            ////////////////////////////////////////////////////////////////////////////////

            virtual void prepareServer (ApplicationServer*);

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief adds features to the application server
            ////////////////////////////////////////////////////////////////////////////////

            virtual void buildApplicationServer (ApplicationServer*);

            ////////////////////////////////////////////////////////////////////////////////
            /// @brief builds the http servers
            ////////////////////////////////////////////////////////////////////////////////

            virtual HttpServer* buildHttpServer (ApplicationHttpServer*, HttpHandlerFactory*);


            ////////////////////////////////////////////////////////////////////////////////
            /// @brief builds the https servers
            ////////////////////////////////////////////////////////////////////////////////

            virtual HttpsServer* buildHttpsServer (ApplicationHttpsServer*, HttpHandlerFactory*);

        };

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief constructs a new rest model
        ////////////////////////////////////////////////////////////////////////////////

        RestModel ();

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief destructs a rest model
        ///
        /// The destructor will delete the crud, authentication, and extensions models.
        ////////////////////////////////////////////////////////////////////////////////

        virtual ~RestModel ();

      public:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief returns the extensions model
        ////////////////////////////////////////////////////////////////////////////////

        Extensions* getExtensions () const {
          return extensions;
        }

      public:


        ////////////////////////////////////////////////////////////////////////////////
        /// @brief called to build the dispatcher queues
        ////////////////////////////////////////////////////////////////////////////////

        virtual void buildQueues (RestServer*, ApplicationServerDispatcher*);


        ////////////////////////////////////////////////////////////////////////////////
        /// @brief called after the server has started
        ////////////////////////////////////////////////////////////////////////////////

        virtual void startupServer (ApplicationServer*);

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief called during shutdown
        ////////////////////////////////////////////////////////////////////////////////

        virtual void shutdownServer ();

      protected:

        ////////////////////////////////////////////////////////////////////////////////
        /// @brief extensions used
        ////////////////////////////////////////////////////////////////////////////////

        Extensions* extensions;
    };
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @ingroup RestServer
/// @brief creates a session model singleton
////////////////////////////////////////////////////////////////////////////////

#define REST_MODEL_SINGLETON(a)                         \
  namespace {                                           \
    a REST_MODEL_INSTANCE;                              \
                                                        \
    triagens::rest::RestModel* restModel () {           \
      return &REST_MODEL_INSTANCE;                      \
    }                                                   \
  }                                                     \
                                                        \
  triagens::rest::RestModel* (*REST_MODEL) () = restModel

////////////////////////////////////////////////////////////////////////////////
/// @ingroup RestServer
/// @brief defines a session model singleton
////////////////////////////////////////////////////////////////////////////////

#define DEFINE_REST_MODEL_SINGLETON(a)                  \
  namespace {                                           \
    triagens::rest::RestModel* restModel () {           \
      return &a;                                        \
    }                                                   \
  }                                                     \
                                                        \
  triagens::rest::RestModel* (*REST_MODEL) () = restModel

#endif
