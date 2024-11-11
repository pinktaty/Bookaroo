"use client"
import React, { useState } from 'react';
import Filters from './components/filterSection';
import GeneratedPrompt from './components/storyGenerated';
import Head from 'next/head';
import {sendPrompt} from "@/services/conectApi";

export default function Home() {
    const [generatedPrompt, setGeneratedPrompt] = useState('');
    const [promptFinished, setPromptFinished] = useState('');

    const handlePromptGenerated = async (prompt) => {
        setGeneratedPrompt(prompt);
        try {
            const response = await sendPrompt(prompt);
            setPromptFinished(response);
        } catch (error) {
            setPromptFinished("Ocurrió un error, favor de intentarlo de nuevo.");
        }
    };

    return (
        <>
            <Head>
                <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
                <title>Bookaroo</title>
                <link rel="preconnect" href="https://fonts.googleapis.com"/>
                <link rel="preconnect" href="https://fonts.gstatic.com" crossOrigin/>
                <link
                    href="https://fonts.googleapis.com/css2?family=Playwrite+GB+S:ital,wght@0,100..400;1,100..400&family=Teachers:ital,wght@0,400..800;1,400..800&display=swap"
                    rel="stylesheet"
                />
            </Head>
            <div className="flex sm:flex-row flex-col items-start justify-center p-3">
                <div className="sm:flex-grow-1 flex flex-col items-center justify-center ">
                    <Filters onPromptGenerated={handlePromptGenerated}/>
                </div>
                <div className="flex-1 flex flex-col items-center">
                    <GeneratedPrompt generatedPrompt={generatedPrompt} promptFinished={promptFinished}/>
                </div>
            </div>
        </>
    );
}
