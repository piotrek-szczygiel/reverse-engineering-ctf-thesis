use rpassword;

fn main() {
    ascii_logo();
    let key = rpassword::read_password_from_tty(Some("key: ")).expect("key read error");

    let input = "example";
    let output = rc4(input.into(), key.into());
    println!("output: {:?}", output);
}

fn rc4(input: Vec<u8>, key: Vec<u8>) -> Vec<u8> {
    let mut state = [0u8; 256];
    for i in 0..state.len() {
        state[i] = i as u8;
    }

    let mut j: usize = 0;
    for i in 0..state.len() {
        j = (j + state[i] as usize + key[i % key.len()] as usize) & 0xff;
        state.swap(i, j);
    }

    let mut output = vec![];

    let mut i: usize = 0;
    let mut j: usize = 0;
    for byte in input {
        i = (i + 1) & 0xff;
        j = (j + state[i] as usize) & 0xff;
        state.swap(i, j);
        output.push(state[(state[i] as usize + state[j] as usize) & 0xff] ^ byte);
    }

    output
}

fn ascii_logo() {
    println!(
        r"
{0}                             _      _  {1}      _    __
{0}                            (_)    | | {1}     | |  / _|
{0} ___ _______ _____   _  __ _ _  ___| | {1}  ___| |_| |_
{0}/ __|_  / __|_  / | | |/ _` | |/ _ \ | {1} / __| __|  _|
{0}\__ \/ / (__ / /| |_| | (_| | |  __/ | {1}| (__| |_| |
{0}|___/___\___/___|\__, |\__, |_|\___|_| {1} \___|\__|_|
{0}                  __/ | __/ |
{0}                 |___/ |___/      {2}2020{3}
",
        "\x1b[0m", "\x1b[1m\x1b[31m", "\x1b[1m\x1b[4m\x1b[5m\x1b[92m", "\x1b[0m"
    );
}
