"use client";
import React, { useState } from 'react';
import Image from "next/image";
import {createPrompt} from "../services/conectApi";


export default function Filters({ onPromptGenerated }) {
    const json = require(`./options.json`);
    const filtersJson = json.filters;
    let filters = [];

    const [selectedValues, setSelectedValues] = useState(
        new Array(filtersJson.length).fill(null)
    );

    const handleButtonClick = (filterIndex, option) => {
        const updatedValues = [...selectedValues];
        updatedValues[filterIndex] = option;
        setSelectedValues(updatedValues);
    };

    const handleGeneratePrompt = () => {
        for (let i = 0; i < selectedValues.length; i++) {
            if (selectedValues[i] === null) {
                return;
            }
        }
        const prompt = createPrompt(selectedValues);
        onPromptGenerated(prompt);
    };

    const renderSelectedValues = () => {
        return (
            <div className="flex flex-col items-start p-4">
                <h5 className="font-bold">Personalización:</h5>
                <ul>
                    {selectedValues.map((value, index) => (
                        <li className="mt-2" key={index}>
                            {json.personalizacion[index]}{value !== null ? value : 'Valor no seleccionado'}
                        </li>
                    ))}
                </ul>
            </div>
        );
    };

    for (let i = 0; i < filtersJson.length; i++) {
        filters.push(
            <div key={i} className="p-4">
                <h4 className="font-bold font-teachers mb-1 flex flex-col items-start">{filtersJson[i].name}</h4>
                {filtersJson[i].options.map((option, optionIndex) => (
                    <button
                        key={optionIndex}
                        onClick={() => handleButtonClick(i, option)}
                        className="font-teachers hover:bg-ligth-purple m-1 p-2 border rounded-2xl border-gray-300 hover:border-bright-purple"
                    >
                        {option}
                    </button>
                ))}
            </div>
        );
    }

    return (
        <div className="flex flex-col bg-white rounded-2xl items-start md:min-h-screen">
            <div className="flex items-start p-3">
                <Image
                    src="/bookaroo.png"
                    alt="bokaroo"
                    width={120}
                    height={50}
                />
            </div>
            {filters}
            {renderSelectedValues()}
            <button className="font-teachers self-center mb-4 p-4 bg-bright-purple text-white hover:bg-dark-purple border-amber-950 rounded-2xl"
                    onClick={handleGeneratePrompt}>
                Genera tu historia
            </button>
        </div>
    );
}
