#include <restinio/core.hpp>

using router_t = restinio::router::express_router_t<>;

std::unique_ptr<router_t> create_request_handler()
{
    std::unique_ptr<router_t> router = std::make_unique<router_t>();

    router->http_get(
        "/",
        [](restinio::request_handle_t req, auto)
        {
            req->create_response()
                .set_body("Hello World!")
                .done();
            return restinio::request_accepted();
        });

    router->http_post(
        "/post-here",
        [](restinio::request_handle_t req, auto)
        {
            req->create_response()
                .set_body("{'data': 'success'}")
                .append_header_date_field()
                .append_header(restinio::http_field_t::server, "Restinio ")
                .done();

            return restinio::request_accepted();
        });

    return router;
}

int main()
{
    using traits_t = restinio::traits_t<restinio::asio_timer_manager_t, restinio::single_threaded_ostream_logger_t, router_t>;

    restinio::run(
        restinio::on_this_thread<traits_t>()
            .port(8080)
            .address("localhost")
            .request_handler(create_request_handler()));

    return 0;
}