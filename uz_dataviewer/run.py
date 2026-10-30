import time


def main(uz):
    # Adapt the variable and value to your firmware before running.
    uz.set_variable("send_field_1", 0.0)
    uz.enable_system()
    time.sleep(1)
    uz.enable_control()
    print("Control enable sent; check the streamed platform state")


if __name__ == "__main__":
    import argparse
    from ultrazohm import Client

    parser = argparse.ArgumentParser(description="UltraZohm measurement")
    parser.add_argument("--endpoint", default="127.0.0.1:19740",
                        help="Acquisition service host:port")
    args = parser.parse_args()
    main(Client(args.endpoint))
