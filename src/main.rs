macro_rules! print_results {
    ($($day:ident),*) => {
        $(
            println!(
                "{} {}:\n\tpart 1: {}\n\tpart 2: {}",
                &stringify!($day)[..3],
                &stringify!($day)[3..],
                $day::silver(),
                $day::gold()
            );
        )*
    };
}

mod helpers;

mod day1;

fn main() {
    print_results![day1];
}
