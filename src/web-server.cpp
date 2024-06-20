#include <restinio/core.hpp>

restinio::request_handling_status_t handler(restinio::request_handle_t req)
{
    if (req->header().method() == restinio::http_method_get() && req->header().request_target() == "/")
    {
        req->create_response()
            .append_header(restinio::http_field::server, "Restinio server")
            .append_header(restinio::http_field::content_type, "text/plain; charset=utf-8")
            .append_header_date_field()
            .set_body("Hello World!!")
            .done();

        return restinio::request_accepted();
    }

    return restinio::request_not_handled();
}

int main()
{
    restinio::run(
        restinio::on_this_thread()
            .port(8080)
            .address("localhost")
            .request_handler(handler));

    return 0;
}