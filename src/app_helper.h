/*
 * nghttp2 - HTTP/2.0 C Library
 *
 * Copyright (c) 2012 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef APP_HELPER_H
#define APP_HELPER_H

#include "nghttp2_config.h"

#include <stdint.h>
#include <cstdlib>
#include <sys/time.h>
#include <poll.h>

#include <map>
#include <chrono>

#include <nghttp2/nghttp2.h>

namespace nghttp2 {

int verbose_on_header_callback(nghttp2_session *session,
                               const nghttp2_frame *frame,
                               const uint8_t *name, size_t namelen,
                               const uint8_t *value, size_t valuelen,
                               void *user_data);

int verbose_on_frame_recv_callback
(nghttp2_session *session, const nghttp2_frame *frame, void *user_data);

int verbose_on_invalid_frame_recv_callback
(nghttp2_session *session, const nghttp2_frame *frame,
 nghttp2_error_code error_code, void *user_data);

int verbose_on_unknown_frame_recv_callback(nghttp2_session *session,
                                           const uint8_t *head,
                                           size_t headlen,
                                           const uint8_t *payload,
                                           size_t payloadlen,
                                           void *user_data);

int verbose_on_frame_send_callback
(nghttp2_session *session, const nghttp2_frame *frame, void *user_data);

int verbose_on_data_recv_callback
(nghttp2_session *session, uint16_t length, uint8_t flags, int32_t stream_id,
 void *user_data);

int verbose_on_data_send_callback
(nghttp2_session *session, uint16_t length, uint8_t flags, int32_t stream_id,
 void *user_data);

// Returns difference between |a| and |b| in milliseconds, assuming
// |a| is more recent than |b|.
template<typename TimePoint>
std::chrono::milliseconds time_delta(const TimePoint& a, const TimePoint& b)
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(a - b);
}

// Resets timer
void reset_timer();

// Returns the duration since timer reset.
std::chrono::milliseconds get_timer();

// Returns current time point.
std::chrono::steady_clock::time_point get_time();

void print_timer();

// Setting true will print characters with ANSI color escape codes
// when printing HTTP2 frames. This function changes a static
// variable.
void set_color_output(bool f);

} // namespace nghttp2

#endif // APP_HELPER_H
