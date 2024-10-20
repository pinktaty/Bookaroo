/** @type {import('tailwindcss').Config} */
module.exports = {
  content: [
    "./src/pages/**/*.{js,ts,jsx,tsx,mdx}",
    "./src/components/**/*.{js,ts,jsx,tsx,mdx}",
    "./src/app/**/*.{js,ts,jsx,tsx,mdx}",
  ],
  theme: {
    extend: {
      fontFamily: {
        playwrite: ["Playwrite GB S", "cursive"],
        teachers: ["Teachers", "sans-serif"]
      },
      colors: {
        background: "var(--background)",
        foreground: "var(--foreground)",
        'ligth-purple': '#C1AAFF',
        'light-yellow-white': '#FFF3CC',
        'bright-purple': '#652FFF',
        'yelloww': '#FFD766',
        'light-grey': '#F2F2F2',
        'dark-purple': '#5008BF',
        'bright-orange': '#FFB700'
      },
    },
  },
  plugins: [],
};
