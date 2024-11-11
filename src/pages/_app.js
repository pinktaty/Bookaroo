import '../styles/globals.css';

import localFont from "next/font/local";

const geistSans = localFont({
    src: "../styles/fonts/GeistVF.woff",
    variable: "--font-geist-sans",
    weight: "100 900",
});

const geistMono = localFont({
    src: "../styles/fonts/GeistMonoVF.woff",
    variable: "--font-geist-mono",
    weight: "100 900",
});

export const metadata = {
    title: "Bookaroo",
    description: "Create your own story!",
};

export default function App({ Component, pageProps }) {
    return (
        <div
            className={`${geistSans.variable} ${geistMono.variable} antialiased`} // Aplícalo al contenedor general
        >
            <Component {...pageProps} />
        </div>
    );
}
